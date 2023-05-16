/***********************************************************************
 * File: Command.h
 * Author: BING-JIA TAN (B11115001)
 * Create Date: 2023-05-15
 * Editor: BING-JIA TAN (B11115001)
 * Update Date: 2023-05-15
 * Description: Describe here
************************************************************************/
#pragma once

#include "Json.h"

// 前->後 指令範例

 // 1. 初始化
	//{
	//	type:"init",
	//}
	//{
	//	success:true,
	//	board:[
	//		{
	//			type:"", // king、queen、rook、bishop、knight、pawn
	//			color:"black", // black、white
	//			position:"A4",
	//		},
	//		...
	//	]
	//}
 // 2. 點格子
	//// 分為兩種情況 1. 點選自己的棋子 2. 點選空格 開全域存
 //  {
	//	type:"click",
 //      position:"{pos}", // 例如: "A2"
 //  }
	//{
	//	success:true,
	//	player:"black", // black、white

	//}
 // 3. 認輸
 //  {
	//	type:"surrender",
 //  }
 // 4. 上一步
	//{
	//	 type:"undo",
	//}
	//{
	//	success:true,
	//	board:[
	//		{
	//			type:"", // king、queen、rook、bishop、knight、pawn
	//			color:"black", // black、white
	//			position:"A4",
	//		},
	//		...
	//	]
	//}
 // 5. 存檔
	//{
	//	type:"save",
	//}
 // 6. 讀檔
	//{
	//	type:"load",
	//}
	//{
	//	success:true,
	//	board:[
	//		{
	//			type:"", // king、queen、rook、bishop、knight、pawn
	//			color:"black", // black、white
	//			position:"A4",
	//		},
	//		...
	//	]
	//}


// 紀錄表
/*
 *
*/




