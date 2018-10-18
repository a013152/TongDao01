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
char receiveBuf[BUFSIZE] = { 0 };

char send_data[BUFSIZE] = { 0 };
char send_IPPort[256] = { 0 };
char rawStr[BUFSIZE] = { 0 };



int curl_callback(void* buffer, size_t size, size_t nmemb, char * useless)  
{  
	printf("recei buff size:%d \n",   (int)(size * nmemb)); 
	if (nmemb > BUFSIZE)
		printf("recei lenght too long\n");
	strncpy(receiveBuf, buffer, nmemb);
	return RES_SUCCESS;  
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
			curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");

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
			
			//设置问非0表示本次操作为post  
			curl_easy_setopt(curl, CURLOPT_POST, 1);


			// 执行操作
			memset(receiveBuf, 0, BUFSIZE);
			int res = curl_easy_perform(curl);

			
			
	// curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");
	
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
void testSaveFile(){

/*curl --data '{"jsonrpc":"2.0","method": "eth_sendTransaction", "params": [{"from": "0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339", "to":"0x9a69b45960b1108540358db141f028645adbc6b9", "data": "0x4f9f075400000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000047646f5472616e7366657252656d61726b28626f6f6c20747970655f202c6164647265737320616464722c2075696e7420616d6f756e742c20737472696e672072656d61726b5f2900000000000000000000000000000000000000000000000000"}], "id": 6}' -H "Content-Type: application/json" -X POST localhost:8101*/

	//int iRet = RES_SUCCESS;
	// 初始化curl
	CURL *curl;
	curl = curl_easy_init();
	// 设置目标url
	curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");	
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	//设置发送数据 
	/*curl --data '{"method":"eth_call","params":[{"from":"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339","to":"0x9a69b45960b1108540358db141f028645adbc6b9","value":"0x0","data": "0x4f9f07540000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000a73617948656c6c6f282900000000000000000000000000000000000000000000"},"latest"],"id":1,"jsonrpc":"2.0"}' -H "Content-Type: application/json" -X POST localhost:8101*/
	char dataBuf[ONE_K*5+1] = {0};
	char szTmp[3] = {0}; 
	
	for (int i = 0; i < ONE_K*5/2; i++)   		
	{
		sprintf(szTmp, "%02X",  (i%10));
		memcpy(&dataBuf[i * 2], szTmp, 2);
	}
	dataBuf[ONE_K*5] = 0;
	
	sprintf(send_data, "{\"method\":\"eth_sendTransaction\",\"params\":[{\"from\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"to\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"gas\":\"0xfffff\",\"data\":\"0x%s\"}],\"id\":1,\"jsonrpc\":\"2.0\"}",dataBuf);
	//sprintf(send_data, "{\"method\":\"eth_accounts\",\"params\":[],\"id\":1,\"jsonrpc\":\"2.0\"}"); //eth_sendTransaction  eth_estimateGas
	printf("send_data:%s\n", send_data);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);
	//对返回的数据进行操作的函数地址 
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);

	//设置问非0表示本次操作为post  
	curl_easy_setopt(curl, CURLOPT_POST, 1);

	
	//设置超时时间
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,5L);
	
	// 执行操作
	memset(receiveBuf, 0, BUFSIZE);
	int res = curl_easy_perform(curl);
	printf("res:%d, receiveBuf:%s\n",res, receiveBuf);
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
	// stpcpy(szfuntionhex,"FFD8FFE000104A46494600010101004800480000FFDB00430006040506050406060506070706080A100A0A09090A140E0F0C1017141818171416161A1D251F1A1B231C1616202C20232627292A29191F2D302D283025282928FFDB0043010707070A080A130A0A13281A161A2828282828282828282828282828282828282828282828282828282828282828282828282828282828282828282828282828FFC0001108013B014003012200021101031101FFC4001A000100030101010000000000000000000000030405020108FFC4002E100100020102040405040301000000000000010203041105213151124161711322323472334281B12391A152FFC40014010100000000000000000000000000000000FFC40014110100000000000000000000000000000000FFDA000C03010002110311003F00FA64000000000000000000000000000000000000000000000000000000000000000000000000000000000719B2D31577BCEDE8A19B5D7B6F18E3C31DFCC1A36BD6B1BDAD111EB282FADC35E9336F68655AD369DED3333EAF01A16E211FB693FCCB99E216F2A47FB51017A3885BCF1C7FB775E215FDD498F696700D7A6AF0DFF76D3EA9E26263789898F460BBC796F8E77A5A601B62960D744ED5CB1B4F785D89898DE39C00000000000000000000000000000000000000000ADABD4C618F0D79DFFA77ABCD1871EFFBA7A4322D33699999DE640BDED7B4DAF3332F00000000000000059D26A670DA2B6E74EDD95806ED6D16889ACEF12F597A2D47C2B786F3F24FFC6A473000000000000000000000000000000000009E51BC8ADAFC9E0C1311D6DC819FAACB39B2CDBCA39422000000000000000000001A7C3B378E938ED3F357A7B3312E9727C2CF5B796FB483640000000000000000000000000000000019BC4EFBE5AD7CA2376931F596F16A6FE93B021000000000000000000000001B5A6BF8F052DE8915786DB7D3EDDA65680000000000000000000000000000000626A39E7C9F94B6D899BF5AFF0094838000000000000000000000001A3C2E7E4BC7AAEA870AE993F85F00000000000000000000000000000001899BF5AFF94B6D8BA98DB3E4F790460000000000000000000000034385F4C9FC2F2970B8FF001DE7D5740000000000000000000000000000000646BA36D55FD79B5D99C4EBB67ACF78054000000000000000000000001A9C3636D3CCF795A43A2AF874B4F5E698000000000000000000000000000000052E295DF1D2DDA765D45A9A7C4C17AF9EDBC031800000000000000000000088DE62204FA3C7F13515ED1CE41AD8EBE1A56BDA367A00000000000000000000000000000000000C6D563F879ED5F2EB089A5C4B178B1C648EB5EBECCD00000000000000000001A7C3B178314DE7ADBFA67E0C73972D691E7D5B711111111D2390000000000000000000000000000000000000131131B4F49636AB0CE1CB31FB679C4B655F5F8BE260998EB5E700C90000000000000000778693972D691E720BDC3716D49C93D67942EBCAC456B158E910F40000000000000000000000000000000000000001899E9F0F35EBDA5C2D7128DB51BF7855000000000000017F8663FAF24FB42835B411B696BEBBC82C000000000000000000000000000000000000000039C97AE3A4DAD3B44033F89FEB57F153779B24E5C96BCF9B800000000000001ABC3EDBE9A23B4CC3296B87E68C793C169F96DFD8350000000000000000000000000000000000000796B56B1BDA6223D54B3EBA237AE28DE7FF00520B59B3530D77BCFB477656A33DB35BE6E55F28477B5AF6F15A6667D5E000000000000000000034349AC8DA29967DACBD1CD829F06A7262E513BD7B4835C56C3ACC59395A7C36F55989DE378000000000000000000000001165D462C5F55B9F68E6095E5A62B1BCCC447AB3F2EBED3CB1D62B1DE552F92D79DEF699F706965D6E2A7D3BDA7D1572EBB2DBE9DAB1E8AA03DBDED79DED699F778000000000000000000000000003BC79B263FA2D30E005EC5AF98FD4AEFEB0B78B518B27D378DFB4F26300DE18D8F51971FD379DBB4F35AC5AFF002CB5FE6017C478F363C9F45A27D120000000008351A9A618DBADFB027E9D55736B71D378AFCF3E8A19B51932CFCD6E5DA3A2204F9B559726FCFC31DA100000000000000000000000000000000000000000000011CA778E52B38B59969CA67C51EAAC035F0EAB1E5E513E1B7694EC15AD3EB2F8F95FE6AFFD806A0E71DEB92B16A4EF0E8106B33FC1A72FAE7A322D336999B4EF3293539272E6B5BCBCBD91800000000000000000000000000000000000000000000000000000025D3E6B61BEF5E71E71DDAF8EF192916ACF2961AFF0CC93BDA93D3AC0280000000000000000000000000000000000000000000000000000000002C682DE1D4D7D778574BA4FB9C7EE0880000000000000000000000000000000000000000000000000000000012E97EE31FE4892E97EE31FE40880000000000000000000000000000000000000000000000000000000012E97EE31FE4892E97EE31FE40FFFD9");
	// szfuntionhex[flen*2] = 0;
	// for(int k = 0; k <  flen*2 ; k++)
	// {
		// if(szfuntionhex2[k] != szfuntionhex[k])
		// {
			// printf("not same\n");
			// break;
		// }
		
	// }
	 

	// 使用CURL调用sendTransaction方法保存到 区块链上
	
	CURL *curl;
	curl = curl_easy_init();
	// 设置目标url
	curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");	
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

	//设置问非0表示本次操作为post  
	curl_easy_setopt(curl, CURLOPT_POST, 1);

	
	//设置超时时间
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,5L);
	
	// 执行操作
	memset(receiveBuf, 0, BUFSIZE);
	
	int res = curl_easy_perform(curl);
	
	printf("res:%d, receiveBuf:%s\n",res, receiveBuf);
	curl_easy_cleanup(curl); 
	
	
	//

	// writeBuf = malloc(flen + 1);
	// HexStrToByte(szFuntionHex,writeBuf,flen*2);
	// writeBuf[flen] = 0;
	// printf("a3.jpg:%s\n",writeBuf);
	// //比较内存中数据的大小
	// bool bSame = true;
	// for(int i = 0; i < flen+1; i++){
		// if(writeBuf[i] != readBuf[i])
		// {
			// bSame = false;
			// break;
		// }
	// }
	// if(bSame){
		// printf("two memory is same!\n");
	// }   
	// else{
		// printf("two memory is different!11\n")  ;
	// }
	
	// //保存到本地
	
	// if ((pf = fopen("a3.jpg", "wb+")) == NULL){
		// printf("write a3.jpg fail！ \n");
	// }else{
		
		// fwrite(writeBuf,flen,1,pf);
	// } 
	
	// free(writeBuf);
	//free(readBuf); 
	
}
int main()
{
	//char outFunctionCode[256] = { 0 };
	//getFunctionCode("sayHello()", outFunctionCode); 

	//testSaveFile(); 
	
	testSaveJPG();
	
	return 0;

}



