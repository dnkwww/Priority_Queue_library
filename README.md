# Priority_Queue_library
 
111上資料結構HW3

[作業說明網頁](https://hackmd.io/@chtsai/2020DS-homework-3)

---

建構一個 priority queue (PQ) 的 library..

函式庫使用說明書.pdf的執行結果指令未分類檔案，在CMD打開根目錄打以下指令執行即可：

```
gcc -c -I./include ./src/PQ.c -o ./obj/PQ.o

ar -cr ./lib/libPQ.a ./obj/PQ.o

gcc -I./include ./test/test.c ./lib/libPQ.a -o ./bin/test.exe

cd bin
test.exe
```
