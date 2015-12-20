#include "runMatcherUtils.h"

// STL headers
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>

// ROOT headers
#include "TFile.h"
#include "TTree.h"
#include "TRegexp.h"

// BOOST headers
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

// Headers from this package
#include "commonRootUtils.h"


std::vector<TLorentzVector> makeTLorentzVectors(std::vector<float> et,
                                                std::vector<float> eta,
                                                std::vector<float> phi) {
    // check all same size
    if (et.size() != eta.size() || et.size() != phi.size()) {
        throw std::range_error("Eta/eta/phi vectors different sizes, cannot make TLorentzVectors");
    }
    std::vector<TLorentzVector> vecs;
    for (unsigned i = 0; i < et.size(); i++) {
        TLorentzVector v;
        v.SetPtEtaPhiM(et.at(i), eta.at(i), phi.at(i), 0);
        vecs.push_back(v);
    }
    return vecs;
}


std::vector<TLorentzVector> makeTLorentzVectors(std::vector<float> et,
                                                std::vector<float> eta,
                                                std::vector<float> phi,
                                                std::vector<short> bx) {
    // check all same size
    if (et.size() != eta.size() || et.size() != phi.size()) {
        throw std::range_error("Eta/eta/phi vectors different sizes, cannot make TLorentzVectors");
    }
    std::vector<TLorentzVector> vecs;
    for (unsigned i = 0; i < et.size(); i++) {
        if (bx.at(i) == 0) {
            TLorentzVector v;
            v.SetPtEtaPhiM(et.at(i), eta.at(i), phi.at(i), 0);
            vecs.push_back(v);
        }
    }
    return vecs;
}


void loadCorrectionFunctions(const TString& filename,
                             std::vector<TF1>& corrFns,
                             const std::vector<float>& etaBins) {

    TFile * corrFile = openFile(filename, "READ");

    // Loop over eta bins
    for (unsigned ind = 0; ind < etaBins.size()-1; ++ind) {
        float etaMin(etaBins[ind]), etaMax(etaBins[ind+1]);
        TString binName = TString::Format("fitfcneta_%g_%g", etaMin, etaMax);
        TF1 * fit = dynamic_cast<TF1*>(corrFile->Get(binName));
        // Make a copy of function and store in vector
        if (fit) {
            TF1 fitFcn(*fit);
            corrFns.push_back(fitFcn);
        } else {
            // throw invalid_argument(binName.Prepend("No TF1 with name ").Data());
            // load in flat function if no suitable one is in file
            TF1 fitFcn(binName, "1");
            corrFns.push_back(fitFcn);
            cout << "No correction fn found for eta bin ";
            cout << etaMin << " - " << etaMax << endl;
            cout << ": Will not correct jets in this bin" << endl;
        }
    }
    corrFile->Close();
}


void correctJets(std::vector<TLorentzVector>& jets,
                 std::vector<TF1>& corrFns,
                 std::vector<float>& etaBins,
                 float minPt) {
    // NB to future self: tried to make corrFns and etaBins const,
    // but lower_bound doesn't like that

    // check corrFn correct size
    if (corrFns.size() != etaBins.size()-1) {
        throw std::range_error("Corrections functions don't match eta bins");
    }

    // Loop over jets, get correct function for given |eta| & apply if necessary
    for (auto& jetItr: jets) {
        // Get eta bin limits corresponding to jet |eta|
        float absEta = fabs(jetItr.Eta());
        auto maxItr = std::lower_bound(etaBins.begin(), etaBins.end(), absEta);
        if (maxItr == etaBins.begin()) {
            throw std::range_error("Max eta != first eta bin");
        }
        auto minItr = maxItr - 1;

        // Get correction fn for this bin
        TF1 corrFn = corrFns[minItr-etaBins.begin()];

        // Get fit range
        double fitMin(0.), fitMax(250.);
        corrFn.GetRange(fitMin, fitMax);

        // Now decide if we should apply corrections
        // Can either use range of fit function, or above some minimum pt
        // Might get rid of former option - get disjoint pt spectrum
        if (((minPt < 0.) && (jetItr.Pt() > fitMin) && (jetItr.Pt() < fitMax))
            || ((minPt >= 0.) && (jetItr.Pt() >= minPt))) {
            // corrFn.Print();
            float newPt = jetItr.Pt() * corrFn.Eval(jetItr.Pt());
            // safeguard against crazy values
            if (newPt < 1000. && newPt > 0.) {
                jetItr.SetPtEtaPhiM(newPt, jetItr.Eta(), jetItr.Phi(), jetItr.M());
            }
        }
    }
}


std::string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string str1 = std::string(dt);
    boost::algorithm::trim(str1);
    return str1;
}


TString removePattern(const TString & str, const TString & pattern) {
    TString suffix(str);
    TRegexp re(pattern);
    // replace the substring matching the regex with ""
    suffix(re) = "";
    if (suffix == "") suffix = str;
    return suffix;
}