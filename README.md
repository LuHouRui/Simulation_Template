# Simulation_Template
WNDCLab Simulation Template

##  檔案說明
### For Topology
env.h env.cpp
Edge.h  Edge.cpp
Node.h  Node.cpp
Link.h  Link.cpp
Request.h Request.cpp
Runiform_rand.h  Runiform_rand.cpp
Topo.cpp
setup.txt
Draw_topo_figure.py
Gen_Topo.sh

### For Method
Simple_Method.cpp
Run_Simple.sh

### For Result
Average.cpp
Draw_result.py

##  完整實驗流程
1. 編譯程式碼
```
make all
```
2. 產出網路
```
//  sh Gen_Topo.sh #Node_Num #Request_Num #Area #Date
//  MM:01~12, dd:01~31
sh Gen_Topo.sh 100 10 10 MMdd
```
3.執行方法
```
//  sh Run_Simple.sh #Node_Num #Request_Num #Area #Date
//  MM:01~12, dd:01~31
sh Run_Simple.sh 100 10 10 MMdd
```
4.重複步驟1~3
由於實驗的結果圖一定是以網路中的某個參數為變數，觀察其變數在變化的過程中，方法的效能變化，因此要根據本身想要的參數與參數變動範圍來去重複以上步驟，如Node 數量從100 ~ 1000進行變動，每次變動增加100個
nodes，所以在結果圖的x軸上就會有10個點。
5.畫出結果圖
```
//  python3 Draw_result.py #Request_Num #Area #Date
//  MM:01~12, dd:01~31
python3 Draw_result.py 10 10 MMdd
```
