all: T2 T3 F6 F7 F8 SF1 SF2

T2: E1
	@echo "Printing Table 2"

T3: E1
	@echo "Printing Table 3"

F6: E1
	@echo "Printing Figure 6"

F7: E2
	@echo "Printing Figure 7"

F8: E1
	@echo "Printing Figure 8"

SF1: E2
	@echo "Printing Supplementary Figure 1"

SF2: E1
	@echo "Printing Supplementary Figure 2"

E1:
	@echo "Running Experiment 1"

E2:
	@echo "Running Experiment 2"
