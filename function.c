#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <curl/curl.h>
#include <cJSON.h>
#include "commonFun.h" 

#define  BUFSIZE	8192
#define  ONE_K   1024
#define RES_SUCCESS 1
#define IP_PORT  "127.0.0.1:8101"
char receiveBuf[BUFSIZE] = { 0 }; 
char send_data[BUFSIZE] = { 0 };
char send_IPPort[256] = { 0 };
char rawStr[BUFSIZE] = { 0 };



int curl_callback(void* buffer, size_t size, size_t nmemb, char * buff)  
{  
	//printf("recei buff size:%d, nmemb:%d, size*nmemb:%d \n", (int)size, (int)nmemb, (int)(size * nmemb)); 
	unsigned long length =0;  //拷贝的长度
	if (nmemb > BUFSIZE)
	{
		printf("recei lenght too long\n");
		length = BUFSIZE -1;
	}else{
		length =size*nmemb;
	}
	strncpy(buff, buffer, length);
	return length;  
}  

/*
//函数：getFunctionCode
//功能：获取函数代码
//参数：参数1 需要计算的函数名称+参数组成的字符串， 参数2 返回的8字节的代码
//返回值： 成功返回 true 
*/
bool getFunctionCode(const char* inFunctionName, char* outFunctionCode)
{
	bool resultFlag = false;
	//1 把参数1转化为十六进制
	//int sourceLen = strlen(inFunctionName);
	//char *szFuntionHex = malloc(sourceLen*2 +1);
	//Hex2Str(inFunctionName, szFuntionHex, sourceLen*2);
	//szFuntionHex[sourceLen*2] = 0;
	//printf("%s:%s\n",inFunctionName,szFuntionHex);


	//2 通过curl 调用eth_call方法， omnicore-cli help getblockchaininfo
	
	//int iRet = RES_SUCCESS;
	// 初始化curl
	printf ("1\n");
	CURL *curl;
	struct curl_slist *headers = NULL;
	curl = curl_easy_init();

	// 设置目标url
	
	// 设置目标url
			curl_easy_setopt(curl, CURLOPT_URL, IP_PORT);

			// 输出header头部信息
			curl_easy_setopt(curl, CURLOPT_HEADER, 0);
			headers = curl_slist_append(headers, "Content-type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 

			//post参数
			
			sprintf(send_data,"{\"method\":\"eth_accounts\",\"params\":[],\"id\":1,\"jsonrpc\":\"2.0\"}" );
			printf("%s\n",send_data);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);

			//对返回的数据进行操作的函数地址 
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, receiveBuf);
			//设置问非0表示本次操作为post  
			curl_easy_setopt(curl, CURLOPT_POST, 1);


			// 执行操作
			memset(receiveBuf, 0, BUFSIZE);
			int res = curl_easy_perform(curl);

			
			
	// curl_easy_setopt(curl, CURLOPT_URL, IP_PORT);
	
	// curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	// 
	// headers = curl_slist_append(headers, "Content-type: application/json");
	// curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	// //设置发送数据 
	// /*curl --data '{"method":"eth_accounts","params":[{"from":"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339","to":"0x9a69b45960b1108540358db141f028645adbc6b9","value":"0x0","data": "0x4f9f07540000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000a73617948656c6c6f282900000000000000000000000000000000000000000000"},"latest"],"id":1,"jsonrpc":"2.0"}' -H "Content-Type: application/json" -X POST localhost:8101*/
	// sprintf(send_data, "{\"method\":\"eth_accounts\",\"params\":[],\"id\":1,\"jsonrpc\":\"2.0\"}");
	

	printf("receiveBuf:%s\n", receiveBuf);

	//3 解码返回的json数据库，获取方法代码


	//4 执行回收资源
	
	curl_easy_cleanup(curl);
	//free(szFuntionHex);
	return resultFlag;
}

//使用transaction 的data 保存数据库
void testSaveFileOnChain(char* dataBuf)
{
	//int iRet = RES_SUCCESS;
	// 初始化curl
	CURL *curl;
	curl = curl_easy_init();
	// 设置目标url
	curl_easy_setopt(curl, CURLOPT_URL, IP_PORT);	
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	//设置发送数据   
	int flen = strlen(dataBuf);
	if(flen < BUFSIZE - 250){
		//sprintf(send_data, "{\"method\":\"eth_sendTransaction\",\"params\":[{\"from\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"to\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"gas\":\"0xfffff\",\"data\":\"0x%s\"}],\"id\":1,\"jsonrpc\":\"2.0\"}",dataBuf);
		sprintf(send_data, "{\"method\":\"eth_sendTransaction\",\"params\":[{\"from\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"gas\":\"0xfffff\",\"data\":\"0x%s\"}],\"id\":1,\"jsonrpc\":\"2.0\"}",dataBuf);
		//printf("send_data:%s\n", send_data); 
	} 
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);
	//对返回的数据进行操作的函数地址 
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, receiveBuf);
	//设置问非0表示本次操作为post  
	curl_easy_setopt(curl, CURLOPT_POST, 1);

	
	//设置超时时间
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,5L);
	
	// 执行操作
	memset(receiveBuf, 0, BUFSIZE);
	int res = curl_easy_perform(curl);
	printf("res:%d, receiveBuf:%s\n",res, receiveBuf);
	//解析json，或者交易hex
	
	
	curl_easy_cleanup(curl);
}

void testSaveJPG()
{
	
	FILE * pf = NULL; char* readbuf = NULL ,* writebuf = NULL;
	if ((pf = fopen("a2.jpg", "rb")) == NULL)
	{
		printf("can not open a2.jpg , exit!\n");
		return ;//exit( 0);
	}
	fseek(pf, 0l, SEEK_END); //移动到文件末尾
	int flen = ftell(pf);
	if(flen > 4096)
		printf("a2.jpg size > 4096 \n");
	readbuf = malloc(flen + 1);
	fseek(pf, 0l, SEEK_SET); //移动到文件头
	fread(readbuf, flen, 1, pf); //读取全部内容
	readbuf[flen] =0;  //结束字符
	fclose(pf);
	
	printf("a2.jpg len:%d  \n",flen);
	char *szfuntionhex = (char*)malloc(flen*2 +1);
	//char *szfuntionhex2 = (char*)malloc(flen*2 +1);
	Hex2Str(readbuf, szfuntionhex, flen);
	szfuntionhex[flen*2] = 0;
	printf("a2.jpg:%s\n",szfuntionhex); 

	// 使用CURL调用sendTransaction方法保存到 区块链上
	
	CURL *curl;
	curl = curl_easy_init();
	// 设置目标url
	curl_easy_setopt(curl, CURLOPT_URL, IP_PORT);	
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	//设置发送数据  
	
	sprintf(send_data, "{\"method\":\"eth_sendTransaction\",\"params\":[{\"from\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"to\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"gas\":\"0xfffff\",\"data\":\"0x%s\"}],\"id\":1,\"jsonrpc\":\"2.0\"}",szfuntionhex);	
	//sprintf(send_data, "{\"method\":\"eth_accounts\",\"params\":[],\"id\":1,\"jsonrpc\":\"2.0\"}"); //eth_sendTransaction  eth_estimateGas
	printf("send_data:%s\n", send_data);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);
	//对返回的数据进行操作的函数地址 
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, receiveBuf);
	
	//设置问非0表示本次操作为post  
	curl_easy_setopt(curl, CURLOPT_POST, 1);

	
	//设置超时时间
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,5L);
	
	// 执行操作
	memset(receiveBuf, 0, BUFSIZE);
	
	int res = curl_easy_perform(curl);
	
	printf("res:%d, receiveBuf:%s\n",res, receiveBuf);
	curl_easy_cleanup(curl); 
	
	
	free(szfuntionhex);
	free(readbuf); 
	
}

int curl_callback_pack(void* buffer, size_t size, size_t nmemb, void * pStRead_)  
{  
	stReadData* pStRead = (stReadData*)pStRead_;
	printf("curl callback recei buff size:%d, nmemb:%d, size*nmemb:%d \n", (int)size, (int)nmemb, (int)(size * nmemb)); 
	unsigned long length =0;  //拷贝的长度
	if (nmemb+pStRead->Offset > BUFSIZE)
	{
		printf("recei lenght too long\n");
		length = BUFSIZE -1;
	}else{
		length =size*nmemb;
	}
	strncpy(&pStRead->pReceivBuf[pStRead->Offset], buffer, length);
	pStRead->Offset += length;
	return length;  
}  

void readTransactionInput(const char* szTxID, char* buff)
{
	CURL *curl;
	curl = curl_easy_init();
	// 设置目标url
	curl_easy_setopt(curl, CURLOPT_URL, IP_PORT);	
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-type: application/json");
	headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	//设置发送数据  
	
	sprintf(send_data, "{\"method\":\"eth_getTransactionByHash\",\"params\":[\"%s\"],\"id\":1,\"jsonrpc\":\"2.0\"}",szTxID);	 
	printf("send_data:%s\n", send_data);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);
	//对返回的数据进行操作的函数地址 
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback_pack);
	char* pBuff = (char*)malloc(BUFSIZE); memset(pBuff,0,BUFSIZE);
	stReadData obj ;obj.Offset = 0;obj.pReceivBuf=pBuff;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&obj);

	//设置问非0表示本次操作为post  
	curl_easy_setopt(curl, CURLOPT_POST, 1); 
	
	//设置超时时间
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,5L); 
	
	int res = curl_easy_perform(curl);
	
	//printf("curl_easy_perform res:%d\n",res);
	if(res != 0){
		char szTemp[256] = {0};
		printfCURLError(res , szTemp);
		printf("%s\n",szTemp);
	}
	curl_easy_cleanup(curl); 
	
	
	//解析json 里的 input 数据
	cJSON * json = cJSON_Parse(obj.pReceivBuf);
	char * json_data = NULL; 
	if (json)
	{	 
		cJSON *resultObj = NULL;
		resultObj = cJSON_GetObjectItem(json, "result");
		if (resultObj){
			
			cJSON *inputObj = cJSON_GetObjectItem(resultObj, "input");
			if(inputObj)
			{
				json_data = cJSON_Print(inputObj);
				if(inputObj->type == cJSON_String)
				{
					//保存数据
					int lenght_ = strlen(inputObj->valuestring);
					if(BUFSIZE > lenght_){ 
						strcpy(buff, inputObj->valuestring);
						 buff[lenght_] = 0;
						char * pdata = &buff[2];  //截取
						cJSON_ReplaceItemInObject(resultObj,"input",cJSON_CreateString(pdata));  //用于代替resultObj对象中input元组的值 
						inputObj = cJSON_GetObjectItem(resultObj, "input");
						strcpy(buff, inputObj->valuestring);
						//printf("getInputData2:%s\n", buff);
					}
					else {
						printf("BUFSIZE:%d < lenght_%d\n", BUFSIZE,lenght_);
					}
				}else {
					printf("input type is not string \n");
				}
			}else{
				printf("input is null\n");
			}
			
		}else{
			printf("result is null\n");
		}
	}
	else{
		printf("json is  null\n");
	} 
	free(pBuff);
}

void saveToFile(char* fileName, char * pdata)
{
	if(pdata[0] == 0)
	{
		printf("save file is null,return!\n");
		return ;
	}
	FILE * pf = NULL;  
	if ((pf = fopen(fileName, "wb+")) == NULL)
	{
		printf("can not open %s!\n",fileName);
		return ;//exit( 0);
	}
	int flen = strlen(pdata); 
	char *fileData = (char*)malloc(flen / 2 + 1);
	HexStrToByte(pdata,fileData,flen);
	fileData[flen / 2] = 0; 
	
	// //保存到本地
	if(fwrite(fileData,flen/2,1,pf)  == flen/2);
		printf("write %s success!\n",fileName);
	fclose(pf); 
	free(fileData); 
}

void testSaveFile01(char * szFile)
{
	FILE * pf = NULL; char* readbuf = NULL ,* writebuf = NULL, *hexBuf;
	if ((pf = fopen(szFile, "rb")) == NULL)
	{
		printf("can not open %s , exit!\n",szFile);
		return ;//exit( 0);
	}
	fseek(pf, 0l, SEEK_END); //移动到文件末尾
	long flen = ftell(pf);	//计算文件的长度
	fseek(pf, 0l, SEEK_SET); //移动到文件头
	printf("File:%s .size:%ld \n", szFile, flen);
	if(flen > 2048)
	{
		readbuf = malloc(2048 +1);
		hexBuf = malloc(4096 + 1);
		int iReadLen =0, iCurenPos = 0, count_= 1; 
		while(!feof(pf)){
			memset(readbuf, 0 ,2048+1);
			memset(hexBuf, 0 ,4096+1);
			iReadLen = 0;
			if((flen - iCurenPos) > 2048){
				iReadLen = 2048;
			}
			else{
				iReadLen = flen - iCurenPos;
			}
			printf("%05d times read %04d bytes ",count_++, iReadLen);
			fread(readbuf, 2048, 1, pf); //读取1次2048的内容
			iCurenPos += iReadLen;
			printf("|||| have read %04d bytes ,current ftell:%08ld\n",  iReadLen, ftell(pf));
			
			Hex2Str(readbuf , hexBuf, iReadLen);
			testSaveFileOnChain(hexBuf);
			
			//break;
		}
	}else{		
		readbuf = malloc(flen + 1);
		fread(readbuf, flen, 1, pf); //读取全部内容
	}
	
	if(readbuf)
	{
		free(readbuf);
	}
	fclose(pf);
	
}

pNode createList()
{
	pNode pNew = NULL,pHead = NULL, pTail=NULL ;
	 pHead = (pNode)malloc(sizeof(Node));      //   分配一个不存放有效数据的头结点  
	 pTail = pHead;   pTail->pNext = NULL;                             //    链表的最后一个节点   //    最后一个节点的指针置为空  
	 pHead->member = "0x43ff6df116d082214f8dd4529c0e7aabc43493e218e7d4bb7760c08223883c61";
	 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0xf851c0cadebc5ad0c83ddfc80f921c73baff617db2a6ad32e9d19eead5ff677c";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew;
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x7dda23a2ccb87628f2353a3c6efcb941f9eb99f4a86b1d3ba3e75f77fcb2d10b";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x281223476afd831291d360f7097259e5523fd825cc9b7d4e5dcf185b776d09bc";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x3693d280d3c6b7d15b94d0b50aff247962ea2675f3915653d57b48ea7deb3ad1";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x71440ce0202772f492749f0cd3c27c33f7c3b055f2f27a5542452db318b5dbbe";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x9ac1448dacdb23c51cbb323f3b66d782c592bc9f975f0e603c21859493e3aa5c";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x76f886cd9484f5c16ec5cb0380f4c1603571c4cc00f7bfcb69f663673374b756";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x068ec944a308847ce997d02687bb9797200e0d6199a47f612fe380489439f1a9";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x6161a35cf8d3dc8ba47bca67a56991448d2a589ff28bc69727df6dd44fa7d377";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x4d0d4d704868be2f643db4eeb04dfe2e38fb64013f544a444483b26a5d216ab7";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x61e9ce06f1b794594abd061fadeeda2836c1909a4c89d33df72308bd4f12e85f";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0xce0365392120954837e3642fdccb5a515ca6f2c6fa3ee04b6a2a7a75abbf9da7";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x8d873a5e513a23a8e076d869b6255550f2f3b5f18505e401c090cee915380227";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0xef7c1bfe92c5f7c841b635c2331a7ae7583d6c15a24a86ee571b8867d47f32d1";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x47806cbe1866125e162dcfc6002cc60176ba04dbaae5fcf2830ee6d4e8c6b35f";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x2f7441b897c86f3aca13088bd694d441817558d44d9e73a4820127272a49a64d";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0xc32892e03f32660c1a99dd552855f5a09836774a4d5b94139700f882071ec0a9";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x80d8f489d25ed88f88da216a0a278e1061aed6ef2496a9f8de602a9ab7a83c49";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x908678d83d318b70de7ee921a69514f3d0451f4f04f3ccf641a9783e695aa1c2";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x2856b6a78a768042acc6fe03c04801c717d3c86ac5cdf0df19052cf71a6d6209";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	pNew=(pNode)malloc(sizeof(Node));pNew->member = "0x64b474ef9a705781117fa79b39ed1df4c822de879f8681ec561817b06836c4d2";pTail->pNext = pNew;pNew->pNext = NULL;pTail = pNew; 
	return pHead;                                    //返回头节点  
}
void freeNode(pNode p){
	if(p->pNext != NULL)
		freeNode(p->pNext);
	free(p);
}
	
void readChainDataToSaveLocal()
{
	FILE * pf = NULL;  int flen = 0;
	char *fileData  = (char*)malloc(2048 + 1);
	char *fileName ="test02.zip";
	char pBuff[BUFSIZE] ={0};
	if ((pf = fopen(fileName, "ab+")) == NULL)
	{
		printf("can not open %s!\n",fileName);
		return ;//exit( 0);
	}
	
	pNode pHead = createList();   //假设已经保存了test01.zip在链上的所有交易hex
	pNode p = pHead;                         //将头节点的指针给予临时节点p  
    while(NULL != p)                                //节点p不为空，循环      
    {  
        printf("%s\n",p->member);                      
		// //读取交易input内容
		memset(pBuff,0,BUFSIZE);
		memset(fileData,0,2048+1);
		readTransactionInput(p->member, pBuff);
		// //保存到本地
		flen = strlen(pBuff); 
		HexStrToByte(pBuff,fileData,flen);
		//printf("pBuff len%lu:%s\n",strlen(pBuff), pBuff);		
		size_t res =fwrite(fileData, flen/2, 1, pf);
		if(res != 1);
		{
			printf("%s write fail error! write return:%lu, flen/2:%d\n", fileName, res, flen/2);
			//break;
		}
        p = p->pNext;   
		//break;		
    }     
	freeNode(pHead); 
	fclose(pf); 
	free(fileData); 
}
int main()
{
	//gcc -o a.out function.c cJSON.c commonFun.c -lcurl
	//char outFunctionCode[256] = { 0 };
	//getFunctionCode("sayHello()", outFunctionCode); 

	//testSaveFile(); 
	
	//testSaveJPG();
	
	 //char* pBuff = (char*)malloc(BUFSIZE); memset(pBuff,0,BUFSIZE);
	// readTransactionInput("0xbc09fdee991399db4934101b06883159abef7b8a31b909704c19b8ee202b53b1", pBuff);
	// printf("getInputData:%s\n", pBuff);
	// saveToFile("a4.jpg", pBuff); 
	// free(pBuff);
	
	//存储test01.zip
	testSaveFile01("test01.zip");
	
	//根据交易hex 读取，还原test01.zip
	//readChainDataToSaveLocal();
	
	 
	return 0;

}



