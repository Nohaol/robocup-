/*
 * main.cpp
 *
 *  Created on: 2014年6月23日
 *      Author: xuf
 */
#include <iostream>
#include "global.h"
#include <stdlib.h>
#include "basicwalk.h"
#include "image.h"


int main()
{

	robot_info.yaw_start=-70;//初始电子罗盘0角与场地0`角的差值  南球门（对着11出口）
	robot_info.yaw_start=162;//北球门
	//euler_init();

	Image_Init();

	/*udp_broadcast_client_init(3838);
	server_sock_init(&client_sock, 8888, "192.168.1.189");*/
	#ifdef GONG_KONG
		fd = portInit("/dev/ttyS0");
	#else
    	fd = portInit("/dev/ttyUSB0");					//调试时注意更改初始化的串口
	#endif

   //update_still();
   delay_sec(1);


    /*if(pthread_create(&game_master_t , NULL, process_game_master, NULL) != 0)
    cout<<"process game_master pthread failed"<<endl;
    cout<<"process game_master pthread succeeded"<<endl;*/

    if(pthread_create(&serial_t, NULL, serial, NULL) != 0)
		cout<<"serial pthread failed"<<endl;
		cout<<"serial pthread succeeded"<<endl;   //头的转向,head,hand


	/*if(pthread_create(&tuoluoyi_t, NULL, tuoluoyi, NULL) != 0)
    	cout<<"tuoluoyi pthread failed"<<endl;
    	cout<<"tuoluoyi pthread succeeded"<<endl;  //wdz10.13*/

    /*if(pthread_create(&fsm_t, NULL, fsm_change, NULL) != 0)
    	cout<<"fsm_change pthread failed"<<endl;
    	cout<<"fsm_change pthread succeeded"<<endl;*/

//    	//2025.3调试：打开摄像头
//    	while(1)
//	{
//		fsm_attack_image();
//        //cout<<"dis:"<<robot_info.ball_dis4robot<<endl;
//		usleep(1);
////		char c = cvWaitKey(1);
////		if(c == 27 )
////		{
////			Image_Clear();
////			exit(0);
////		}
//		//cout<<1111;
//	}


    if(pthread_create(&image_t, NULL, image, NULL) != 0)
		cout<<"image pthread failed"<<endl;
		cout<<"image pthread succeeded"<<endl;

    /*if(pthread_create(&head_t, NULL, process_head, NULL) != 0)
		cout<<"process head pthread failed"<<endl;
		cout<<"process head pthread succeeded"<<endl;*/

//   if(pthread_create(&body_t, NULL, process_body, NULL) != 0)
//		cout<<"process body pthread failed"<<endl;
//		cout<<"process body pthread succeeded"<<endl;

//


	void *pthread_result;

	pthread_join(serial_t, &pthread_result);   //腿无法控制
//	pthread_join(body_t, &pthread_result);
	pthread_join(image_t, &pthread_result);
	//pthread_join(fsm_t, &pthread_result);
	//pthread_join(tuoluoyi_t, &pthread_result);
	//pthread_join(head_t, &pthread_result);
	//pthread_join(game_master_t, &pthread_result);
    getchar();

	return 0;
}



