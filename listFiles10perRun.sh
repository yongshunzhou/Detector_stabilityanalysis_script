


for n in $(seq 6000 1 6200)
do
   found_files="samweb list-files 'data_tier full-reconstructed and run_number ${n} and run_type protodune-sp and data_stream physics and application reco'|sort"
   declare -i number_scan_files=$(eval ${found_files}|wc -l)
   scan_root_files=$(eval ${found_files})
   indiv_scan_root_files=($scan_root_files)
   echo ${number_scan_files}" Files found in Run ${n}:"
   if [ $number_scan_files -gt 9 ]
   then

   eval ${found_files}

   ########## Time to run through each indiv. raw data file ##########
   for n in $(seq 0 1 9)
   #for n in 0 # if you would like to check the first file of run only
   do
#    echo "--------------------------------------------------"
    data_file=${indiv_scan_root_files[${n}]}
    echo 'working on file ' ${data_file}
    find_file_loc="samweb locate-file ${data_file}"
    locs_file=$(eval ${find_file_loc}) #multiple locations
    loc_file_temp_temp=${locs_file##*enstore:} # "cern-eos:" for CERN, "enstore:" for /pnfs/ (FNAL), "castor:" for tape
    loc_file_temp=${loc_file_temp_temp%(*}
    loc_file=(${loc_file_temp%\ *})
#    echo ""
#    echo ""

#    echo "All file locations: "
#    echo ${locs_file}
#    echo ""
#    echo ""
#    echo "Location of (ensotre) file: ${loc_file}/${data_file}" #[0]##*:}/${data_file}"
    echo ${loc_file}/${data_file}>>Run_list_10perRun.txt

   # #### Getting Run info for my output txt file name- probably not needed for most #####
   # output_file_name_temp=${data_file%.*}
   # output_file_name=${output_file_name_temp##*_run}
   #
   # ##### This is the command (stored as string "analyze_data") to execute larsoft with a specific fcl file (here I used "RunSSPWaveforms.fcl") on the raw data file
   # analyze_data="lar -c RunSSPWaveforms.fcl root://eospublic.cern.ch:1094/${loc_file[0]}/${data_file}"
#  #  analyze_data="lar -c RunRawDecoder.fcl root://eospublic.cern.ch:1094/${loc_file[0]}/${data_file}"

   # ### eval executes the analyze_data string as a bash command
   # eval ${analyze_data}  >>  Run_${output_file_name}.txt #I outputed this to a txt file, per raw root file intentionally- feel free to modify
   # #eval ${analyze_data}  >>  Run_${output_file_name}.txt #I outputed this to a txt file, per raw root file intentionally- feel free to modify
   # echo ${analyze_data} # see what is being executed
   # #sed -i 1,62d Run_${output_file_name}.txt # This removes the first 723 lines of the output txt file, which is needed for my python posted filtering script
   # #mv RunRawDecoderTFile.root Run_${output_file_name}.root
    done
  fi
done
