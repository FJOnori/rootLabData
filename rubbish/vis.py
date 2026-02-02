import uproot
import numpy
import matplotlib.pyplot as plt
import pandas as pd


file_45F6379E_344 = uproot.open("data/out-feb-45F6379E-000345.root")
# file_4944044F_344 = uproot.open("data/out-feb-4944044F-000344.root")
# file_45F6379E_345 = uproot.open("data/out-feb-45F6379E-000345.root")
# file_4944044F_345 = uproot.open("data/out-feb-4944044F-000345.root")

# ['sumTotalHits', 'B01_timestamp', 'B01_tag', 'B01_totalHits', 'B01_PMT1Hits', 'B01_PMT2Hits', 'B01_evid', 'B01_PMT1', 'B01_PMT2', 'B01_MAR1_ADC', 'B01_MAR2_ADC', 'B01_PMT1_ADC', 'B01_PMT2_ADC']
 

print(file_45F6379E_344.keys())
tree = file_45F6379E_344["mdfTree;1"] 

print(tree.keys())

df = tree.arrays(["B01_PMT1_ADC"], library="pd")

print(df)

plt.hist(df["B01_PMT1_ADC"])
plt.show()
# print(file_45F6379E_344.classnames())
# print(file_45F6379E_344.all_members())