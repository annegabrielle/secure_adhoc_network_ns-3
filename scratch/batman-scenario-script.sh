#!/bin/sh

#PAUSE="0 200 400 600 800 900"
#TRIALS="1 2 3 4 5 6 7 8 9 10"

#Varying pause times and amount of trials for each pause time 
PAUSE="0 "
TRIALS="1 2 3 4 5 6 7 8 9 10"

echo WiFi Experiment Example

pCheck=`which sqlite3`
if [ -z "$pCheck" ]
then
  echo "ERROR: This script requires sqlite3."
  exit 255
fi

pCheck=`which gnuplot`
if [ -z "$pCheck" ]
then
  echo "ERROR: This script requires gnuplot."
  exit 255
fi

pCheck=`which sed`
if [ -z "$pCheck" ]
then
  echo "ERROR: This script requires sed."
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
    waf --run "annestest --format=db --batman=0 --seed=$trial --pause=$pause --ns3::YansWifiPhy::TxPowerStart=8.9048 --ns3::YansWifiPhy::TxPowerEnd=8.9048 --run=run-$pause"
  done
done


# Create SQL command
CMD="SELECT rx.run, avg(cast(rx.value as real)/cast(tx.value as real)) 
		FROM Singletons rx, Singletons tx 
		WHERE rx.variable = 'rx' AND tx.variable='tx'
		GROUP BY rx.run
		ORDER BY rx.run ASC;"
#CMD="SELECT s.run, avg(s.value) FROM Singletons s GROUP BY abs(s.run);"

#mv ../../data.db .

# Query the SQLite Database
sqlite3 -noheader data.db "$CMD" > annestest.data

# Parse the data
sed -i "s/run-//" batman-scenario.data
sed -i "s/|/   /" batman-scenario.data

# Run gnuplot script and create graph
gnuplot batman-scenario.gnuplot

echo "Done; data stored in batman-scenario.data, plot created"