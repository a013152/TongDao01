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
	printf("recei buff size:%d \n",   (int)nmemb); 
	if (nmemb > BUFSIZE)
		printf("recei lenght too long\n");
	strncpy(receiveBuf, buffer, nmemb);
	return RES_SUCCESS;  
}  

/*
//������getFunctionCode
//���ܣ���ȡ��������
//����������1 ��Ҫ����ĺ�������+������ɵ��ַ����� ����2 ���ص�8�ֽڵĴ���
//����ֵ�� �ɹ����� true 
*/
bool getFunctionCode(const char* inFunctionName, char* outFunctionCode)
{
	bool resultFlag = false;
	//1 �Ѳ���1ת��Ϊʮ������
	//int sourceLen = strlen(inFunctionName);
	//char *szFuntionHex = malloc(sourceLen*2 +1);
	//Hex2Str(inFunctionName, szFuntionHex, sourceLen*2);
	//szFuntionHex[sourceLen*2] = 0;
	//printf("%s:%s\n",inFunctionName,szFuntionHex);


	//2 ͨ��curl ����eth_call������ omnicore-cli help getblockchaininfo
	
	//int iRet = RES_SUCCESS;
	// ��ʼ��curl
	printf ("1\n");
	CURL *curl;
	struct curl_slist *headers = NULL;
	curl = curl_easy_init();

	// ����Ŀ��url
	
	// ����Ŀ��url
			curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");

			// ���headerͷ����Ϣ
			curl_easy_setopt(curl, CURLOPT_HEADER, 0);
			headers = curl_slist_append(headers, "Content-type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 

			//post����
			
			sprintf(send_data,"{\"method\":\"eth_accounts\",\"params\":[],\"id\":1,\"jsonrpc\":\"2.0\"}" );
			printf("%s\n",send_data);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);

			//�Է��ص����ݽ��в����ĺ�����ַ 
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
			
			//�����ʷ�0��ʾ���β���Ϊpost  
			curl_easy_setopt(curl, CURLOPT_POST, 1);


			// ִ�в���
			memset(receiveBuf, 0, BUFSIZE);
			int res = curl_easy_perform(curl);

			
			
	// curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");
	
	// curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	// 
	// headers = curl_slist_append(headers, "Content-type: application/json");
	// curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	// //���÷������� 
	// /*curl --data '{"method":"eth_accounts","params":[{"from":"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339","to":"0x9a69b45960b1108540358db141f028645adbc6b9","value":"0x0","data": "0x4f9f07540000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000a73617948656c6c6f282900000000000000000000000000000000000000000000"},"latest"],"id":1,"jsonrpc":"2.0"}' -H "Content-Type: application/json" -X POST localhost:8101*/
	// sprintf(send_data, "{\"method\":\"eth_accounts\",\"params\":[],\"id\":1,\"jsonrpc\":\"2.0\"}");
	

	printf("receiveBuf:%s\n", receiveBuf);

	//3 ���뷵�ص�json���ݿ⣬��ȡ��������


	//4 ִ�л�����Դ
	
	curl_easy_cleanup(curl);
	//free(szFuntionHex);
	return resultFlag;
}

//ʹ��transaction ��data �������ݿ�
void testSaveFile(){

/*curl --data '{"jsonrpc":"2.0","method": "eth_sendTransaction", "params": [{"from": "0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339", "to":"0x9a69b45960b1108540358db141f028645adbc6b9", "data": "0x4f9f075400000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000047646f5472616e7366657252656d61726b28626f6f6c20747970655f202c6164647265737320616464722c2075696e7420616d6f756e742c20737472696e672072656d61726b5f2900000000000000000000000000000000000000000000000000"}], "id": 6}' -H "Content-Type: application/json" -X POST localhost:8101*/

	//int iRet = RES_SUCCESS;
	// ��ʼ��curl
	CURL *curl;
	curl = curl_easy_init();
	// ����Ŀ��url
	curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");	
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	//���÷������� 
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
	//�Է��ص����ݽ��в����ĺ�����ַ 
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);

	//�����ʷ�0��ʾ���β���Ϊpost  
	curl_easy_setopt(curl, CURLOPT_POST, 1);

	
	//���ó�ʱʱ��
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,5L);
	
	// ִ�в���
	memset(receiveBuf, 0, BUFSIZE);
	int res = curl_easy_perform(curl);
	printf("res:%d, receiveBuf:%s\n",res, receiveBuf);
	curl_easy_cleanup(curl);
}

void testSaveJPG()
{
	
	FILE * pf = NULL; char* readBuf = NULL ,* writeBuf = NULL;
	if ((pf = fopen("a2.jpg", "rb")) == NULL)
	{
		printf("can not open a2.jpg , exit!\n");
		return ;//exit( 0);
	}
	fseek(pf, 0L, SEEK_END); //�ƶ����ļ�ĩβ
	int flen = ftell(pf);
	if(flen > 4096)
		printf("a2.jpg size > 4096 \n");
	readBuf = malloc(flen + 1);
	fseek(pf, 0L, SEEK_SET); //�ƶ����ļ�ͷ
	fread(readBuf, flen, 1, pf); //��ȡȫ������
	readBuf[flen] =0;  //�����ַ�
	fclose(pf);
	
	printf("a2.jpg len:%d  %s\n",flen, readBuf);
	char *szFuntionHex = (char*)malloc(flen*2 +1);
	
	Hex2Str(readBuf, szFuntionHex, flen*2);
	szFuntionHex[flen*2] = 0;
	printf("a2.jpg:%s\n",szFuntionHex);
	
	 

	// ʹ��CURL����sendTransaction�������浽 ��������
		
	CURL *curl;
	curl = curl_easy_init();
	// ����Ŀ��url
	curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8101");	
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);	
	
	if(BUFSIZE > (flen*2 + 230))
	{ 
		sprintf(send_data, "{\"method\":\"eth_sendTransaction\",\"params\":[{\"from\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"to\":\"0xf58c93ceaeffbb91f45c83022ade9cfe5ef19339\",\"gas\":\"0xfffff\",\"data\":\"0x%s\"}],\"id\":1,\"jsonrpc\":\"2.0\"}",szFuntionHex);	
		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send_data);
		//�Է��ص����ݽ��в����ĺ�����ַ 
	
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);

		//�����ʷ�0��ʾ���β���Ϊpost  
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		
			// ִ�в���
		memset(receiveBuf, 0, BUFSIZE);
		int res = curl_easy_perform(curl);
		printf("res:%d, receiveBuf:%s\n",res, receiveBuf);
	}else{
		printf("File's langth : %d over Buf leng%d", flen*2 + 230 , BUFSIZE);
	}	
	curl_easy_cleanup(curl);
	
	
	//

	// writeBuf = malloc(flen + 1);
	// HexStrToByte(szFuntionHex,writeBuf,flen*2);
	// writeBuf[flen] = 0;
	// printf("a3.jpg:%s\n",writeBuf);
	// //�Ƚ��ڴ������ݵĴ�С
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
	
	// //���浽����
	
	// if ((pf = fopen("a3.jpg", "wb+")) == NULL){
		// printf("write a3.jpg fail�� \n");
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



