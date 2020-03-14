for x in ./tsp_test_cases/*.txt; do
	echo "Running $x"
	python3 nn.py $x
	#./tsp_test_cases/tsp-verifier.py "$x" "$x.tour"
done
