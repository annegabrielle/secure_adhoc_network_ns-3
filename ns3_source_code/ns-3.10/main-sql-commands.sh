# Create SQL command to get packet delivery ratio
PDR_CMD="SELECT rx.run, avg(cast(rx.value as real)/cast(tx.value as real)) 
		FROM Singletons rx, Singletons tx 
		WHERE rx.variable = 'onoffRx' AND tx.variable='onoffTx'
		GROUP BY rx.run
		ORDER BY rx.run ASC;"

# Get OnOff packet delay results
DELAY_CMD="SELECT onoff.run, (avg(onoff.value)/1000000000) 
	FROM Singletons onoff
	WHERE onoff.variable = 'onoffDelay-average'
	GROUP BY onoff.run;"

# Get MAC packet delay results 
MAC_CMD="SELECT mac.run, (avg(mac.value)/1000000000) 
	FROM Singletons mac
	WHERE mac.variable = 'macDelay-average'
	GROUP BY mac.run;"

# Amount transmitted and received BATMAN packets AVG!
BATMAN_CMD="SELECT batmant.run, batmant.value, batmanr.value 
	FROM Singletons batmant, Singletons batmanr
	WHERE batmant.variable = 'batmanTx' AND batmanr.variable = 'batmanRx'
	GROUP BY batmant.run;"

# Amount transmitted and received DSDV packets AVG!
DSDV_CMD="SELECT dsdvt.run, dsdvt.value, dsdvr.value 
	FROM Singletons dsdvt, Singletons dsdvr
	WHERE dsdvt.variable = 'dsdvTx' AND dsdvr.variable = 'dsdvRx'
	GROUP BY dsdvt.run;"

# Get everything!
ALL_CMD="SELECT * FROM Singletons;"

# Query the SQLite Database
sqlite3 -noheader data.db "$ALL_CMD" > test.data

# Parse the data
sed -i "s/run-//" test.data
sed -i "s/|/   /" test.data

echo "Done; data parsed!"
