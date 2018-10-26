cc = gcc
prom = a.out
source = function.c commonFun.c cJSON.c
lib = -lcurl

$(prom):$(source)
	$(cc) -o $(prom) $(source) $(lib)

#a.out:function.c commonFun.c cJSON.c
#	gcc -o a.out function.c commonFun.c cJSON.c -lcurl


