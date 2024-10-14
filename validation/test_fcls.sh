#
# test_fcls.sh - runs fcl files to make sure that they complete successfully
# Note: requires relevant filelists in a directory above this one
#

log_file="test_fcls.log"
rm ${log_file}

echo -n "from_mcs-mockdata.fcl... "
mu2e -c fcl/from_mcs-mockdata.fcl -S ../filelists/mcs.mu2e.ensemble-1BB-CEDIOCRYCosmic-2400000s-p95MeVc-Triggered.MDC2020ae_perfect_v1_3.art.list --TFileName nts.ntuple.mock.root -n 100 > ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-mockdata_noMC.fcl... "
mu2e -c fcl/from_mcs-mockdata_noMC.fcl -S ../filelists/mcs.mu2e.ensemble-1BB-CEDIOCRYCosmic-2400000s-p95MeVc-Triggered.MDC2020ae_perfect_v1_3.art.list --TFileName nts.ntuple.mockNoMC.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-primary.fcl... "
mu2e -c fcl/from_mcs-primary.fcl -S ../filelists/mcs.mu2e.CeEndpointOnSpillTriggered.MDC2020ae_best_v1_3.art.list --TFileName nts.ntuple.primary.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-mixed.fcl... "
mu2e -c fcl/from_mcs-mixed.fcl -S ../filelists/mcs.mu2e.CeEndpointMix2BBTriggered.MDC2020ae_best_v1_3.art.list --TFileName nts.ntuple.mixed.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-extracted.fcl... "
mu2e -c fcl/from_mcs-extracted.fcl -S ../filelists/mcs.mu2e.CosmicCRYExtractedCatTriggered.MDC2020ae_best_v1_3.art.list --TFileName nts.ntuple.extracted.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-ceSimReco.fcl... "
mu2e -c fcl/from_mcs-ceSimReco.fcl -s mcs.owner.val-ceSimReco.dsconf.seq.art --TFileName nts.ntuple.ceSimReco.root >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-mockdata_separateTrkBranches.fcl... "
mu2e -c fcl/from_mcs-mockdata_separateTrkBranches.fcl -S ../filelists/mcs.mu2e.ensemble-1BB-CEDIOCRYCosmic-2400000s-p95MeVc-Triggered.MDC2020ae_perfect_v1_3.art.list --TFileName nts.ntuple.mockSepTrkBranches.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_mcs-mockdata_selectorExample.fcl... "
mu2e -c fcl/from_mcs-mockdata_selectorExample.fcl -S ../filelists/mcs.mu2e.ensemble-1BB-CEDIOCRYCosmic-2400000s-p95MeVc-Triggered.MDC2020ae_perfect_v1_3.art.list --TFileName nts.ntuple.mockSelector.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "from_dig-mockdata.fcl... "
mu2e -c fcl/from_dig-mockdata.fcl -S ../filelists/dig.mu2e.ensemble-1BB-CEDIOCRYCosmic-2400000s-p95MeVc-Triggered.MDC2020ae_perfect_v1_3.art.list --TFileName nts.ntuple.dig.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "creating v6 file for validation script... "
mu2e -c fcl/from_mcs-mockdata.fcl -S ../filelists/mcs.mu2e.ensemble-1BB-CEDIOCRYCosmic-2400000s-p95MeVc-Triggered.MDC2020ae_perfect_v1_3.art.list --TFileName nts.ntuple.v6.root -n 100 >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi

echo -n "creating validation file... "
root -l -b -q validation/create_val_file.C\(\"nts.ntuple.v6.root\",\"val.ntuple.v6.root\"\) >> ${log_file} 2>&1
if [ $? == 0 ]; then
    echo "OK"
else
    echo "FAIL"
fi
