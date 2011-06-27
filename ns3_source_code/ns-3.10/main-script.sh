#!/bin/sh

PAUSE="0 100 200 300 400 500 600 700 800 900"
TRIALS="1 2 3 4 5 6 7 8 9 10"

#PAUSE="0"
#TRIALS="1 2"

echo WiFi Experiment Example

pCheck=`which sqlite3`
if [ -z "$pCheck" ]
then
  echo "ERROR: This script requires sqlite3 (wifi-example-sim does not)."
  exit 255
fi

pCheck=`which gnuplot`
if [ -z "$pCheck" ]
then
  echo "ERROR: This script requires gnuplot (wifi-example-sim does not)."
  exit 255
fi

pCheck=`which sed`
if [ -z "$pCheck" ]
then
  echo "ERROR: This script requires sed (wifi-example-sim does not)."
  exit 255
fi

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:bin/

# Remove existing database
if [ -e data.db ]
then
  echo "Kill data.db? (y/n)"
  read ANS
  if [ "$ANS" = "yes" -o "$ANS" = "y" ]
  then
    echo Deleting database
    rm data.db
  fi
fi



# Compile the simulation scenario with the different parameters, and run the number of trials
for pause in $PAUSE
do
  for trial in $TRIALS
  do
    echo
    echo Pause time $pause, Trial $trial
    export NS_GLOBAL_VALUE="RngRun=$trial"
    ./waf --run "main-scenario --format=db --batman=1 --pause=$pause --start=30 --stop=930 --sources=20"
  done
done

#--ns3::YansWifiPhy::TxPowerStart=8.9048 --ns3::YansWifiPhy::TxPowerEnd=8.9048

# Create SQL command to get packet delivery ratio
#CMD="SELECT rx.run, avg(cast(rx.value as real)/cast(tx.value as real)) 
#		FROM Singletons rx, Singletons tx 
#		WHERE rx.variable = 'rx' AND tx.variable='tx'
#		GROUP BY rx.run
#		ORDER BY rx.run ASC;"

# Create SQL command to get packet delay in seconds
#CMD="SELECT avgD.run, (avg(avgD.value)/1000000000) 
#	From Singletons avgD
#	WHERE variable = 'onoffDelay-average'
#	GROUP BY avgD.run;"

#CMD="SELECT s.run, avg(s.value) FROM Singletons s GROUP BY abs(s.run);"

#mv ../../data.db .

# Query the SQLite Database
#sqlite3 -noheader data.db "$CMD" > annestest_v2.data

# Parse the data
#sed -i "s/run-//" annestest.data
#sed -i "s/|/   /" annestest.data

# Run gnuplot script and create graph
#gnuplot dsdv_pdr.gnuplot

echo "Done; data stored in annestest_v2.data!"
