# Asterix in Switzerland

* flows

Once you have come up with the right formulation as flows, this problem is quite simple. The idea is to construct a graph of provinces that models the flow of money. For any province with a positive balance, we add a supply. For any province with a negative balance, we add a demand. We also add an edge for each debt relation. Now, observe that the min source-target-cut is precisely the set of provinces that owes the least (either to other provinces/or the central bank). Also observe that its balance is the sum of all positive balances. Thus, we have a free standing union if and only if the flow is strictly less than the sum of all positive balances.
