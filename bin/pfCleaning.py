#!/usr/bin/env python

"""
Plot things investigating PF jet cleaning (energy fractions, multiplicities)
"""

import ROOT
import binning
import common_utils as cu
import os
import random
import string
import math
import re

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptFit(1111)
ROOT.TH1.SetDefaultSumw2(True)
ROOT.gStyle.SetPalette(55)
ROOT.gStyle.SetNumberContours(100)
ROOT.gErrorIgnoreLevel = 1 # turn off the printing output


fractions = ['nhef', 'chef', 'pef', 'eef', 'mef']
multiplicities = ['chMult', 'nhMult', 'phMult', 'elMult', 'muMult']
sources = ['Neutral Hadron', 'Charged Hadron', 'Photon', 'Electron', 'Muon']

# TightLepVeto jetID cuts
eta_central = 'TMath::Abs(etaRef) < 2.4'
tight_lep_veto_cuts = ['nhef < 0.9', 'pef < 0.9', 'chMult+nhMult+phMult+elMult+muMult > 1', 'mef < 0.8']
tight_lep_veto_cuts.extend(['(%s && %s)' % (c, eta_central) for c in ['chef > 0', 'chMult+elMult+muMult > 0', 'eef < 0.9']])

def random_word(length):
   return ''.join(random.choice(string.lowercase + string.uppercase) for i in range(length))


def generate_canvas(title="", width=1200, height=900):
    """Generate a standard TCanvas for all plots.
    Can optionally pass in title, width and height.
    """
    c = ROOT.TCanvas("c"+random_word(5), title, width, height)
    c.SetTicks(1, 1)
    return c


def generate_legend(x1=0.66, y1=0.7, x2=0.88, y2=0.88):
    """Generate a standard TLegend. Can optionally pass in co-ordinates. """
    leg = ROOT.TLegend(x1, y1, x2, y2)
    return leg


def plot_cumulative_energy(tree, cut=None, title='Cumulative Energy Fraction',
                           log=False, oDir=os.getcwd(), output='cumulative_energy.pdf'):
    """Plot cumulative energy fraction"""
    cut = cut or ''
    c = generate_canvas()
    if log:
        c.SetLogy()
    leg = generate_legend(x1=0.4, x2=0.6)
    stack = ROOT.THStack('hst', '')
    for i in range(len(fractions)):
        var = '+'.join(fractions[:i+1])
        hname = 'h' + ''.join(fractions[:i+1])
        nbins, fmin, fmax = 60, 0, 1.2
        # h = ROOT.TH1F(hname, '', nbins, fmin, fmax)
        tree.Draw('%s>>%s(%d, %f, %f)' % (var, hname, nbins, fmin, fmax), cut)
        h = ROOT.gROOT.FindObject(hname)
        h.SetFillColor(binning.eta_bin_colors[i])
        h.SetLineColor(binning.eta_bin_colors[i])
        h.SetFillStyle(1001)
        h.Draw()
        stack.Add(h)
        if i == 0:
            leg.AddEntry(h, sources[i], 'LF')
        else:
            leg.AddEntry(h, '+ ' + sources[i], 'LF')
    stack.Draw('HISTE')
    stack.SetTitle(title + ';Energy Fraction;')
    leg.Draw()
    c.SaveAs(os.path.join(oDir, output))


def plot_energy_var(pairs_tree, var, var_min=0, var_max=10, var_title=None,
                    logZ=False, normX=False, cut=None, title=None,
                    oDir=os.getcwd(), output='rsp_energy.pdf'):
    """Plot energy fractions vs variable 2D hist, for each energy source, on one big canvas.

    var: string of varibale name in tree
    var_min, var_max: cuts to put on response range
    var_title: variable description for axis title
    logZ: make Z axis logartithmic
    normX: normalise each X bin such that integral of all y values = 1.
    cut: cut to apply (no need to include var range)
    title: title to put on each plot
    oDir: output directory for plot
    output: output filename
    """
    var_cut = '%s < %d && %s > %d' % (var, var_max, var, var_min)
    cut = var_cut if not cut else '%s && %s' % (cut, var_cut)
    var_title = var_title or ''
    c = generate_canvas(width=1800, height=1200)
    c.Divide(3,2)
    hists = []
    for i, fraction in enumerate(fractions):
        c.cd(i+1)
        ROOT.gPad.SetTicks(1, 1)
        if logZ:
            ROOT.gPad.SetLogz()
        hname = 'h2d' + fraction
        # nbins_var = (var_max - var_min) / 0.05
        nbins_var = 200
        nbins_frac, fmin, fmax = 200, 0, 1.2
        pairs_tree.Draw('%s:%s>>%s(%d, %f, %f, %d, %f, %f)' % (fraction, var, hname,
                                                               nbins_var, var_min, var_max,
                                                               nbins_frac, fmin, fmax),
                        cut, 'GOFF' if normX else 'COLZ')
        h = ROOT.gROOT.FindObject(hname)
        h.SetTitle('%s;%s;%s Energy Fraction' % (title, var_title, sources[i]))
        h.SetTitleOffset(1.2, 'XY')
        if normX:
            hnew = cu.norm_vertical_bins(h)
            hnew.Draw('COLZ')
            ROOT.SetOwnership(hnew, False)
            # hists.append(hnew)
    c.SaveAs(os.path.join(oDir, output))


def plot_l1_pf(pairs_tree,
               logZ=True,
               cut=None,
               cleaning_cut=None,
               title=None,
               oDir=os.getcwd(), output='pt_ptRef.png'):
    """
    Plot pt(L1) vs pt(PF)
    """
    cut = cut or '1'
    cleaning_cut = cleaning_cut or '1'
    total_cut = '(%s) && (%s)' % (cut, cleaning_cut)
    title = title or ''
    c = generate_canvas()
    if logZ:
        c.SetLogz()

    nbins_pt, pt_min, pt_max = 200, 0, 400

    # With cleaning cut
    hname = 'hpt_ptref_cleaning'
    pairs_tree.Draw("pt:ptRef>>%s(%d, %f, %f, %d, %f, %f)" % (hname, nbins_pt, pt_min, pt_max, nbins_pt, pt_min, pt_max),
                    total_cut,
                    "COLZ")
    h = ROOT.gROOT.FindObject(hname)
    h.SetTitle('%s;p_{T}^{PF} [GeV];p_{T}^{L1} [GeV]' % total_cut)
    h.SetTitleOffset(1.2, 'XY')
    draw_diag_rsp(pt_max)
    c.SaveAs(os.path.join(oDir, output))

    if cleaning_cut != '1':
        # Inverse of cleaning cut
        inv_cut = '(%s) && !(%s)' % (cut, cleaning_cut)
        hname = 'hpt_ptref_cleaning_diff'
        pairs_tree.Draw("pt:ptRef>>%s(%d, %f, %f, %d, %f, %f)" % (hname, nbins_pt, pt_min, pt_max, nbins_pt, pt_min, pt_max),
                        inv_cut,
                        "COLZ")
        h = ROOT.gROOT.FindObject(hname)
        h.SetTitle('%s;p_{T}^{PF} [GeV];p_{T}^{L1} [GeV]' % inv_cut)
        h.SetTitleOffset(1.2, 'XY')
        draw_diag_rsp(pt_max)
        output_name = os.path.splitext(output)[0] + '_diff' + os.path.splitext(output)[1]
        c.SaveAs(os.path.join(oDir, output_name))


def draw_diag_rsp(max_pt):
    # lines of constant response
    line1 = ROOT.TLine(0, 0, max_pt, max_pt)
    line1.SetLineStyle(1)
    line1.SetLineWidth(2)
    line1.SetLineColor(ROOT.kMagenta)
    line1.Draw()
    ROOT.SetOwnership(line1, False)

    # line1p25 = ROOT.TLine(0, 0, max_pt / 1.25, max_pt)
    # line1p25.SetLineWidth(2)
    # line1p25.Draw()

    # line1p5 = ROOT.TLine(0, 0, max_pt / 1.5, max_pt)
    # line1p5.SetLineWidth(2)
    # line1p5.Draw()

    # line0p75 = ROOT.TLine(0, 0, max_pt, max_pt * 0.75)
    # line0p75.SetLineWidth(2)
    # line0p75.Draw()

    # line0p5 = ROOT.TLine(0, 0, max_pt, max_pt * 0.5)
    # line0p5.SetLineWidth(2)


def plot_rsp_pt(pairs_tree,
                pt_var='pt',
                pt_title='p_{T}',
                pt_min=0,
                pt_max=400,
                logZ=True,
                normX=True,
                cut=None,
                cleaning_cut=None,
                title=None,
                oDir=os.getcwd(), output='pt_ptRef.png'):
    """
    Plot response vs pt
    """
    cut = cut or '1'
    cleaning_cut = cleaning_cut or '1'
    total_cut = '(%s) && (%s)' % (cut, cleaning_cut)
    title = title or ''
    c = generate_canvas()
    if logZ:
        c.SetLogz()

    nbins_pt = 200
    nbins_rsp, rsp_min, rsp_max = 200, 0, 5

    # With cleaning cut
    hname = 'hrsp_pt'
    pairs_tree.Draw("rsp:%s>>%s(%d, %f, %f, %d, %f, %f)" % (pt_var, hname, nbins_pt, pt_min, pt_max, nbins_rsp, rsp_min, rsp_max),
                    total_cut,
                    "COLZ")
    h = ROOT.gROOT.FindObject(hname)
    h.SetTitle('%s;%s;response (p_{T}^{L1} / p_{T}^{PF})' % (total_cut, pt_title))
    h.SetTitleOffset(1.2, 'XY')
    if normX:
        hnew = cu.norm_vertical_bins(h)
        hnew.Draw("COLZ")
    draw_horizontal_rsp(pt_max)
    c.SaveAs(os.path.join(oDir, output))

    if cleaning_cut != '1':
        # Inverse of cleaning cut
        inv_cut = '(%s) && !(%s)' % (cut, cleaning_cut)
        hname = 'hrsp_pt_diff'
        pairs_tree.Draw("rsp:%s>>%s(%d, %f, %f, %d, %f, %f)" % (pt_var, hname, nbins_pt, pt_min, pt_max, nbins_rsp, rsp_min, rsp_max),
                        inv_cut,
                        "COLZ")
        h = ROOT.gROOT.FindObject(hname)
        h.SetTitle('%s;%s;response (p_{T}^{L1} / p_{T}^{PF})' % (total_cut, pt_title))
        h.SetTitleOffset(1.2, 'XY')
        if normX:
            hnew = cu.norm_vertical_bins(h)
            hnew.Draw("COLZ")
        draw_horizontal_rsp(pt_max)
        output_name = os.path.splitext(output)[0] + '_diff' + os.path.splitext(output)[1]
        c.SaveAs(os.path.join(oDir, output_name))


def draw_horizontal_rsp(max_pt):
    # lines of constant response
    line1 = ROOT.TLine(0, 1, max_pt, 1)
    line1.SetLineStyle(1)
    line1.SetLineWidth(2)
    line1.SetLineColor(ROOT.kMagenta)
    line1.Draw()
    ROOT.SetOwnership(line1, False)


if __name__ == "__main__":
    # L1 Ntuple file
    ntuple_filename = '/hdfs/user/ra12451/L1JEC/CMSSW_7_6_0_pre7/L1JetEnergyCorrections/Stage2_Run260627/Express/run260627_expressNoJEC.root'
    f_ntuple = cu.open_root_file(ntuple_filename)
    reco_tree = cu.get_from_file(f_ntuple, 'l1JetRecoTree/JetRecoTree')

    # Matched pairs file
    pairs_filename = '/users/ra12451/L1JEC/CMSSW_7_6_0_pre7/src/L1Trigger/L1JetEnergyCorrections/pairs.root'
    pairs_filename = '/hdfs/user/ra12451/L1JEC/CMSSW_7_6_0_pre7/L1JetEnergyCorrections/Stage2_Run260627/pairs/pairs_Express_data_ref10to5000_l10to5000_dr0p4_noCleaning.root'
    f_pairs = cu.open_root_file(pairs_filename)
    pairs_tree = cu.get_from_file(f_pairs, 'valid')

    plot_dir = '/users/ra12451/L1JEC/CMSSW_7_6_0_pre7/src/L1Trigger/L1JetEnergyCorrections/Run260627/pfCleaning/'

    # Plot cumulative contributions
    # ------------------------------------------------------------------------
    # SLOW!
    # plot_cumulative_energy(reco_tree,
    #                        cut='TMath::Abs(eta) < 0.348 && et > 20',
    #                        title='Cumulative Energy Fraction (|#eta^{PF}| < 0.348, p_{T}^{PF} > 20 GeV, not matched to L1) (Run 260627)',
    #                        log=True,
    #                        oDir=plot_dir,
    #                        output='cumulative_energy_ptRef20_eta_0_0p348_log.pdf')

    # plot_cumulative_energy(reco_tree,
    #                        cut='TMath::Abs(eta) < 0.348 && et > 20',
    #                        title='Cumulative Energy Fraction (|#eta^{PF}| < 0.348, p_{T}^{PF} > 20 GeV, not matched to L1) (Run 260627)',
    #                        log=False,
    #                        oDir=plot_dir,
    #                        output='cumulative_energy_ptRef20_eta_0_0p348.pdf')

    # plot_cumulative_energy(pairs_tree,
    #                        cut='TMath::Abs(etaRef) < 0.348 && ptRef > 20',
    #                        title='Cumulative Energy Fraction (|#eta^{PF}| < 0.348, p_{T}^{PF} > 20 GeV, matched to L1) (Run 260627)',
    #                        log=True,
    #                        oDir=plot_dir,
    #                        output='cumulative_energy_matched_ptRef20_eta_0_0p348_log.pdf')

    # plot_cumulative_energy(pairs_tree,
    #                        cut='TMath::Abs(etaRef) < 0.348 && ptRef > 20',
    #                        title='Cumulative Energy Fraction (|#eta^{PF}| < 0.348, p_{T}^{PF} > 20 GeV, matched to L1) (Run 260627)',
    #                        log=False,
    #                        oDir=plot_dir,
    #                        output='cumulative_energy_matched_ptRef20_eta_0_0p348.pdf')

    rsp_title = 'response (p_{T}^{L1} / p_{T}^{PF})'

    # Plot correlations
    # ------------------------------------------------------------------------
    #
    # Look at contributions to big responses
    # plot_energy_var(pairs_tree, var='rsp', var_min=0, var_max=20,
    #                 var_title=rsp_title,
    #                 logZ=True, normX=True,
    #                 cut='TMath::Abs(eta) < 0.348 && ptRef > 20',
    #                 title='|#eta^{L1}| < 0.348, p_{T}^{PF} > 20 GeV (Run 260627)',
    #                 oDir=plot_dir,
    #                 output='rsp_fractions_big_rsp.png')

    # # # Look at contributions to small responses
    # plot_energy_var(pairs_tree, var='rsp', var_min=0, var_max=1,
    #                 var_title=rsp_title,
    #                 logZ=True, normX=True,
    #                 cut='TMath::Abs(eta) < 0.348 && ptRef > 20',
    #                 title='|#eta^{L1}| < 0.348, p_{T}^{PF} > 20 GeV (Run 260627)',
    #                 oDir=plot_dir,
    #                 output='rsp_fractions_small_rsp.png')

    # plot_energy_var(pairs_tree, var='ptRef', var_min=0, var_max=1000,
    #                 var_title='p_{T}^{PF} [GeV]',
    #                 logZ=True, normX=True,
    #                 cut='TMath::Abs(eta) < 0.348 && ptRef > 20',
    #                 title='|#eta^{L1}| < 0.348, p_{T}^{PF} > 20 GeV (Run 260627)',
    #                 oDir=plot_dir,
    #                 output='ptRef_fractions.png')

    # plot_energy_var(pairs_tree, var='etaRef', var_min=-3, var_max=3,
    #                 var_title='#eta^{PF}',
    #                 logZ=True, normX=True,
    #                 cut='ptRef > 20',
    #                 title='p_{T}^{PF} > 20 GeV (Run 260627)',
    #                 oDir=plot_dir,
    #                 output='eta_fractions.png')

    # plot_energy_var(pairs_tree, var='phiRef', var_min=-ROOT.TMath.Pi(), var_max=ROOT.TMath.Pi(),
    #                 var_title='#phi^{PF}',
    #                 logZ=True, normX=True,
    #                 cut='TMath::Abs(etaRef) < 0.348 && ptRef > 20',
    #                 title='0 < #eta^{PF} < 0.348, p_{T}^{PF} > 20 GeV (Run 260627)',
    #                 oDir=plot_dir,
    #                 output='phi_fractions_eta_0_0p348.pdf')

    # plot_energy_var(pairs_tree, var='phiRef', var_min=-ROOT.TMath.Pi(), var_max=ROOT.TMath.Pi(),
    #                 var_title='#phi^{PF}',
    #                 logZ=True, normX=True,
    #                 cut='TMath::Abs(etaRef) > 1.74 && TMath::Abs(etaRef) < 3 && ptRef > 20',
    #                 title='1.74 < #eta^{PF} < 3, p_{T}^{PF} > 20 GeV (Run 260627)',
    #                 oDir=plot_dir,
    #                 output='phi_fractions_eta_1p74_3.pdf')

    # for ef, name in zip(fractions, sources):
    #     plot_energy_var(pairs_tree, var=ef, var_min=0, var_max=1.2,
    #                     var_title=name + ' Energy Fraction',
    #                     logZ=True, normX=True,
    #                     cut='ptRef > 20 && TMath::Abs(eta) < 0.348',
    #                     title='0 < #eta^{PF} < 0.348, p_{T}^{PF} > 20 GeV (Run 260627)',
    #                     oDir=plot_dir,
    #                     output=ef+'_fractions.png')

    # Make before/after/diffs of cleaning cuts
    # ------------------------------------------------------------------------
    #
    eta_cut = 'TMath::Abs(eta) < 0.348'
    # plot_l1_pf(pairs_tree,
    #            logZ=True,
    #            cut='pt < 400 && ptRef < 400 && %s' % (eta_cut),
    #            cleaning_cut=None,
    #            title='|#eta^{L1}| < 0.348',
    #            oDir=plot_dir, output='pt_ptRef_eta_0_0p348.png')

    plot_rsp_pt(pairs_tree,
                pt_var='pt', pt_min=0, pt_max=400, pt_title='p_{T}^{L1} [GeV]',
                logZ=True,
                normX=True,
                cut='pt < 400 && %s' % (eta_cut),
                cleaning_cut=None,
                title='|#eta^{L1}| < 0.348',
                oDir=plot_dir, output='rsp_pt_eta_0_0p348.png')

    plot_rsp_pt(pairs_tree,
                pt_var='ptRef', pt_min=0, pt_max=400, pt_title='p_{T}^{PF} [GeV]',
                logZ=True,
                normX=True,
                cut='ptRef < 400 && %s' % (eta_cut),
                cleaning_cut=None,
                title='|#eta^{L1}| < 0.348',
                oDir=plot_dir, output='rsp_ptRef_eta_0_0p348.png')

    for id_cut in tight_lep_veto_cuts:
        print id_cut
        app = id_cut.replace('(', '')
        app = re.split(r'<|>', app)[0].strip()
        plot_l1_pf(pairs_tree,
                   logZ=True,
                   cut='pt < 400 && ptRef < 400 && %s' % (eta_cut),
                   cleaning_cut=id_cut,
                   title='|#eta^{L1}| < 0.348',
                   oDir=plot_dir, output='pt_ptRef_eta_0_0p348_%s.png' % app)

        plot_rsp_pt(pairs_tree,
                    pt_var='pt', pt_min=0, pt_max=400, pt_title='p_{T}^{L1} [GeV]',
                    logZ=True,
                    normX=True,
                    cut='pt < 400 && %s' % (eta_cut),
                    cleaning_cut=id_cut,
                    title='|#eta^{L1}| < 0.348',
                    oDir=plot_dir, output='rsp_pt_eta_0_0p348_%s.png' % app)

        plot_rsp_pt(pairs_tree,
                    pt_var='ptRef', pt_min=0, pt_max=400, pt_title='p_{T}^{PF} [GeV]',
                    logZ=True,
                    normX=True,
                    cut='ptRef < 400 && %s' % (eta_cut),
                    cleaning_cut=id_cut,
                    title='|#eta^{L1}| < 0.348',
                    oDir=plot_dir, output='rsp_ptRef_eta_0_0p348_%s.png' % app)

    plot_l1_pf(pairs_tree,
               logZ=True,
               cut='pt < 400 && ptRef < 400 && %s' % (eta_cut),
               cleaning_cut=' && '.join(tight_lep_veto_cuts),
               title='|#eta^{L1}| < 0.348',
               oDir=plot_dir, output='pt_ptRef_eta_0_0p348_all.png')

    plot_rsp_pt(pairs_tree,
                pt_var='pt', pt_min=0, pt_max=400, pt_title='p_{T}^{L1} [GeV]',
                logZ=True,
                normX=True,
                cut='pt < 400 && %s' % (eta_cut),
                cleaning_cut=' && '.join(tight_lep_veto_cuts),
                title='|#eta^{L1}| < 0.348',
                oDir=plot_dir, output='rsp_pt_eta_0_0p348_all.png')

    plot_rsp_pt(pairs_tree,
                pt_var='ptRef', pt_min=0, pt_max=400, pt_title='p_{T}^{PF} [GeV]',
                logZ=True,
                normX=True,
                cut='ptRef < 400 && %s' % (eta_cut),
                cleaning_cut=' && '.join(tight_lep_veto_cuts),
                title='|#eta^{L1}| < 0.348',
                oDir=plot_dir, output='rsp_ptRef_eta_0_0p348_all.png')

    f_ntuple.Close()
    f_pairs.Close()