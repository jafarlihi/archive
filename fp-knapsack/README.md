# fp-knapsack

This is a typical 0-1 Knapsack problem. There are whole books written on the topic (e.g. [Knapsack Problems](https://link.springer.com/book/10.1007/978-3-540-24777-7)) and I haven't really read them so I can't really say if my solution is as optimal as it gets but it is better than the typical bruteforce solution.

The common algorithmic strategies for this are bruteforce and dynamic programming. Bruteforce solution has time complexity of O(n^2). Dynamic programming approach used here however has time complexity of O(n*T), where "n" is number of transactions and "T" is the maximum time we have for processing transactions.

## Results
50ms: $4139.43
60ms: $4675.71
90ms: $6972.29
1000ms: $35471.79

## Run
Run with `go run main.go`

## Output
Output is replicated below:
```
Maximum amount: 35471.79
Transactions chosen for 1000ms total time:
&{ID:cbab486d-3774-424b-bf3b-6cf3377274c1 Amount:888.63 BankCountryCode:ie}
&{ID:650084cb-7b02-487d-8669-1241257e0e6a Amount:532.96 BankCountryCode:ca}
&{ID:efa28d62-73cb-48f9-90d7-d83e689195dc Amount:967.23 BankCountryCode:us}
&{ID:25031525-71ab-41a3-8c77-2e1d64ae9e4a Amount:948.14 BankCountryCode:us}
&{ID:48bd00ed-7cc5-48db-a5ae-157584929289 Amount:502.04 BankCountryCode:us}
&{ID:c4298f08-a71b-4c7e-8527-3e8748e8903a Amount:709.5 BankCountryCode:ky}
&{ID:66dce8ee-a6ff-40fd-ad54-7be89449d644 Amount:424.73 BankCountryCode:us}
&{ID:240dcafb-c29f-48ae-9db9-c50d443c12ba Amount:835.66 BankCountryCode:br}
&{ID:b3e4cc12-e01c-40b6-bdd5-d97484bf4988 Amount:514.81 BankCountryCode:us}
&{ID:b3d93e5f-7a4a-4536-a4dc-b993a4ed38cc Amount:911.36 BankCountryCode:ie}
&{ID:4eb1bd9a-ae09-4121-ad1f-3599105a1146 Amount:580.61 BankCountryCode:ca}
&{ID:0868cc1d-82b2-4b68-9bcd-8123168a6370 Amount:835.15 BankCountryCode:us}
&{ID:17ec7b62-d1ec-45e9-be43-2b0dc7cbf11f Amount:724.03 BankCountryCode:us}
&{ID:156c4926-9fbb-41b9-be87-67ff0349d682 Amount:888.82 BankCountryCode:br}
&{ID:6c605900-3904-4fe0-9478-ae2555dd4cf6 Amount:936.35 BankCountryCode:ky}
&{ID:bbb355c6-b5b9-4ff6-a90a-6e37b117ebb9 Amount:649.34 BankCountryCode:mx}
&{ID:57cfe0ab-3c3a-40d7-a146-809ca90e8576 Amount:541.46 BankCountryCode:mx}
&{ID:a6d6449a-431a-40e3-a3c7-ea65c90a76a9 Amount:986.88 BankCountryCode:mx}
&{ID:7f7c9752-e0c8-4533-9011-fef7383b1351 Amount:645.92 BankCountryCode:ca}
&{ID:e7b4bda3-16c1-4aec-85b3-38446ecad303 Amount:182.61 BankCountryCode:us}
&{ID:3f6389c4-d70b-4af7-818b-480fd3005324 Amount:664.88 BankCountryCode:us}
&{ID:6db9cef9-e465-46bf-a22d-964d6a11b6a6 Amount:556.29 BankCountryCode:ca}
&{ID:cbadc919-53e4-48a8-9103-1498a89a0c75 Amount:677.74 BankCountryCode:ca}
&{ID:a48e4235-55a0-4655-b6b2-ba4d5da46912 Amount:892.14 BankCountryCode:ky}
&{ID:9ea6e2bb-2aa1-4092-a96b-51a89f69d3e0 Amount:904.14 BankCountryCode:br}
&{ID:e00a179e-06d7-4b29-9bf8-17bdcea19f00 Amount:571.5 BankCountryCode:mx}
&{ID:3c4e4268-db1e-46d5-a4b4-aa2c962b6e3f Amount:314 BankCountryCode:mx}
&{ID:b946f41a-b5bf-4c3f-84c4-2e8d9d67b7b1 Amount:783.7 BankCountryCode:mx}
&{ID:64be1005-575b-47b4-a8a3-c120d81b8936 Amount:757.54 BankCountryCode:mx}
&{ID:f6eb62b8-5b8f-4184-a0ea-7706abcd075a Amount:310.17 BankCountryCode:mx}
&{ID:8f1e0979-8a8e-4073-b277-6016ee2a72af Amount:846.55 BankCountryCode:mx}
&{ID:2b549664-9d09-45f0-8c7d-dacf2e7502ce Amount:972.91 BankCountryCode:uk}
&{ID:64da9fd2-5e64-4cb9-8f95-42688b8a6ca2 Amount:941.87 BankCountryCode:ky}
&{ID:17df6906-460a-4493-b6e8-8f4a51d892c6 Amount:871.93 BankCountryCode:br}
&{ID:fba6a3df-2b6c-4537-a3b2-b684d51b2842 Amount:947.55 BankCountryCode:br}
&{ID:0dd4d698-3070-4d6a-aa2b-333088075ca6 Amount:886 BankCountryCode:mx}
&{ID:c922e7b8-ba6e-444a-a2fe-0455be0f4241 Amount:844.38 BankCountryCode:mx}
&{ID:f8495698-234c-44a1-a133-2dd8597c1d1e Amount:992.19 BankCountryCode:nl}
&{ID:3fd4aa8d-2c8a-4d86-876b-ba79bd27e80a Amount:856.71 BankCountryCode:ca}
&{ID:438f9d1e-3180-40ee-85ee-df8cb7eed998 Amount:864.98 BankCountryCode:ky}
&{ID:ac9059be-5610-4fdb-aaa0-8363ae79f508 Amount:887.46 BankCountryCode:ca}
&{ID:dfcdb17c-2ca2-4cf8-a9e7-b60850a1bcdc Amount:766.69 BankCountryCode:ca}
&{ID:3f726449-e61b-4d78-8d83-38f2d8988035 Amount:867 BankCountryCode:br}
&{ID:e2a19808-e1a9-4ac7-989d-e767e6acd585 Amount:441.43 BankCountryCode:ca}
&{ID:d6279533-a331-49bd-8878-dcf4a1067087 Amount:520.71 BankCountryCode:mx}
&{ID:b4ea3b8f-3435-4a72-bdbe-da2e5848ee09 Amount:932.96 BankCountryCode:ky}
&{ID:4c2aa8cb-7117-4411-ac36-c756e980bfff Amount:469.37 BankCountryCode:mx}
&{ID:df340fdc-d0b4-4863-82f9-a7de1033a0f6 Amount:922.79 BankCountryCode:ie}

For 50ms:
Maximum amount: 4139.43
For 60ms:
Maximum amount: 4675.71
For 90ms:
Maximum amount: 6972.29
For 1000ms:
Maximum amount: 35471.79
```
