/*********************************************************************************************************************
*               Copyright(c) 2020, Vcare Corporation. All rights reserved.
**********************************************************************************************************************
* @file     vcHr02DEBUG.c
* @brief    心率血样模式下需要传出的数据(数据格式)
* @details  
             
* @author
* @date
* @version  V1.9.2
**********************************************************************************************************************
*/


/*
* 血氧模式下需要传出的数据
*
*/
	for (i=0; i<ppgLength; i++)
	{
		vcxxSendDugBuff[algoCallNum*18+0] = sampleData->ppgValue[2*algoCallNum]>>8&0xff;
		vcxxSendDugBuff[algoCallNum*18+1] = sampleData->ppgValue[2*algoCallNum]&0xff;
		vcxxSendDugBuff[algoCallNum*18+2] = sampleData->ppgValue[2*algoCallNum+1]>>8&0xff;
		vcxxSendDugBuff[algoCallNum*18+3] = sampleData->ppgValue[2*algoCallNum+1]&0xff;
		vcxxSendDugBuff[algoCallNum*18+4] = algoInputData.axes.x>>8&0xff;
		vcxxSendDugBuff[algoCallNum*18+5] = algoInputData.axes.x&0xff;
		vcxxSendDugBuff[algoCallNum*18+6] = algoInputData.axes.y>>8&0xff;
		vcxxSendDugBuff[algoCallNum*18+7] = algoInputData.axes.y&0xff;
		vcxxSendDugBuff[algoCallNum*18+8] = algoInputData.axes.z>>8&0xff;
		vcxxSendDugBuff[algoCallNum*18+9] = algoInputData.axes.z&0xff;
		vcxxSendDugBuff[algoCallNum*18+10] = systemParam.bloodOxygenValue;
		vcxxSendDugBuff[algoCallNum*18+11] = sampleData->pdResValue[1];
		vcxxSendDugBuff[algoCallNum*18+12] = sampleData->pdResValue[2];
		vcxxSendDugBuff[algoCallNum*18+13] = sampleData->currentValue[1];
		vcxxSendDugBuff[algoCallNum*18+14] = sampleData->currentValue[2];
		vcxxSendDugBuff[algoCallNum*18+15] = sampleData->psValue;
		vcxxSendDugBuff[algoCallNum*18+16] = vcSportFlag;
		vcxxSendDugBuff[algoCallNum*18+17] = vcxxDugIrgCnt;
		vcxxDugIrgCnt++;
	}



/*
 * 心率模式下需要传出的数据
 *
*/
	for (i=0; i<ppgLength; i++)
	{	
		vcxxSendDugBuff[i*15] = algoInputData.ppgSample>>8&0xff;
		vcxxSendDugBuff[i*15+1] = algoInputData.ppgSample&0xff;
		vcxxSendDugBuff[i*15+2] = algoInputData.axes.x>>8&0xff;
		vcxxSendDugBuff[i*15+3] = algoInputData.axes.x&0xff;
		vcxxSendDugBuff[i*15+4] = algoInputData.axes.y>>8&0xff;
		vcxxSendDugBuff[i*15+5] = algoInputData.axes.y&0xff;
		vcxxSendDugBuff[i*15+6] = algoInputData.axes.z>>8&0xff;
		vcxxSendDugBuff[i*15+7] = algoInputData.axes.z&0xff;
		vcxxSendDugBuff[i*15+8] = drvHeartVcxxGetValue()&0xff;
		vcxxSendDugBuff[i*15+9] = sampleData->pdResValue[0];
		vcxxSendDugBuff[i*15+10] = sampleData->currentValue[0];
		vcxxSendDugBuff[i*15+11] = sampleData->envValue[2];
		vcxxSendDugBuff[i*15+12] = sampleData->preValue[0];
		vcxxSendDugBuff[i*15+13] = sampleData->psValue;
		vcxxSendDugBuff[i*15+14] = vcxxDugIrgCnt;
		vcxxDugIrgCnt++;
	}
