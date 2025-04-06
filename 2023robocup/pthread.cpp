/*
 * pthread.cpp
 *
 *  Created on: 2014年9月19日
 *      Author: xuf
 */

#include "global.h"
/************************************线程*********************************************/

//图像线程
void *image(void *arg)
{
	while(1)
	{
		fsm_attack_image();
        //cout<<"dis:"<<robot_info.ball_dis4robot<<endl;
		usleep(1);
//		char c = cvWaitKey(1);
//		if(c == 27 )
//		{
//			Image_Clear();
//			exit(0);
//		}
		//cout<<1111;
	}
	return (void *)"image pthread return!";
}

//身体动作线程
void *process_body(void *arg)
{
	while(1)
	{
		fsm_attack_body();
		usleep(1);
	}
	return (void *)"body process pthread finish.";
}
//头部动作线程
void *process_head(void *arg)
{

	while(1)
	{
	fsm_attack_head();
	usleep(1);
	}
	return (void *)"head process pthread finish.";
}

//WDZ10.13 陀螺仪线程

void *tuoluoyi(void *arg)
{

	char r_buf[1024];
    bzero(r_buf,1024);

    fd_1 = uart_open(fd_1,"/dev/ttyUSB1");/*串口号/dev/ttySn,USB口号/dev/ttyUSBn */
    if(fd_1 == -1)
    {
        fprintf(stderr,"uart_open error\n");
        exit(EXIT_FAILURE);
    }

    if(uart_set(fd_1,BAUD,8,'N',1) == -1)
    {
        fprintf(stderr,"uart set failed!\n");
        exit(EXIT_FAILURE);
    }

	FILE *fp_1;
	fp_1 = fopen("Record.txt","w");
	int parsesec=0;
    while(1)
    {
        ret = recv_data(fd_1,r_buf,44);
        if(ret == -1)
        {
            fprintf(stderr,"uart read failed!\n");
            exit(EXIT_FAILURE);
        }
        parsesec++;
		for (int i=0;i<ret;i++) {fprintf(fp_1,"%2X ",r_buf[i]);ParseData(r_buf[i]);}
        delay_sec(0.1);

    }

    ret = uart_close(fd_1);
    if(ret == -1)
    {
        fprintf(stderr,"uart_close error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
	return (void *)"tuoluoyi process pthread finish.";
}

//裁判盒线程
void * process_game_master(void *arg)
{
		while (1)
		{
			 recv_game_control_data(get_ref_buf );
			 get_info(get_ref_buf );

			 usleep(1);
		}


	return (void *)"game master pthread finish.";
}

//串口线程 发送步态数据
void *serial(void *arg)
{
	while(1){
	if(send_serial_flag ==false)
	{
		serial_head(); //把初始化数据读入到USB
		delay_sec(0.005);
		serial_legs();  //将speed写到USB
		delay_sec(0.005);
		serial_hands();  //hands
		delay_sec(0.005);

	}
//	image_update();

		usleep(1);
	}

	return (void *)"serial pthread finish.";
}



//head:0




void *fsm_change(void *arg)
{


	while(1)
		{
//		cout<<"head:"<<robot_info.robot_state<<endl;

			if(robot_info.fall_info==1||robot_info.fall_info==2)
			{
				//delay_sec(0.5);

				//if(robot_info.fall_info==1||robot_info.fall_info==2)

				robot_info.robot_state = climb_up;

			}
			else
			{
					   switch(robot_info.robot_state)
						{
								case search_ball:
												 if(robot_info.ball_find == true)
														 {
															robot_info.robot_state = chase_ball;
															cout<<"head:"<<robot_info.robot_state<<endl;
															robot_info.fsm_unlocked = false;
//															  cout<<"robot_info.fsm_unlocked 1= "<<robot_info.fsm_unlocked<<endl;

															}
											  break;
								case chase_ball:

													if(!robot_info.ball_find)
															{

																  robot_info.robot_state = search_ball;
																  cout<<"head:"<<robot_info.robot_state<<endl;
	//															  cout<<"robot_info.fsm_unlocked 2= "<<robot_info.fsm_unlocked<<endl;
						//							  	  	  	  	 robot_info.ball_dis4robot = 50;

															  }
													  if(robot_info.ball_find&&(robot_info.ball_dis4robot <= DisMin1))
															  {
									  	  	  	  		            time0=get_time();
																	robot_info.robot_state =round_yaw;
																	cout<<"head:"<<robot_info.robot_state<<endl;

	//																  cout<<"robot_info.fsm_unlocked 3= "<<robot_info.fsm_unlocked<<endl;

															  }
											break;
							   case round_yaw:

								              //  cout<<"robot_info.yaw="<<robot_info.yaw<<endl;
													if((robot_info.yaw<=20.00&&robot_info.yaw>=-20.00))
															{

																robot_info.robot_state =search_goal;
																cout<<"head:"<<robot_info.robot_state<<endl;
		//														  cout<<"robot_info.fsm_unlocked 4= "<<robot_info.fsm_unlocked<<endl;

															 }
													else if((get_time()-time0)>30)
													{
														robot_info.robot_state =search_goal;
														cout<<"head:"<<robot_info.robot_state<<endl;
													}



											 break;
							  case search_goal:
	//`							  robot_info.fsm_unlocked = false;
	//							  cout<<"robot_info.fsm_unlocked 5= "<<robot_info.fsm_unlocked<<endl;
													  if(robot_info.fsm_unlocked==true)
															 {
														        time0=get_time();
																 robot_info.robot_state = adjust_ball;
																 cout<<"head:"<<robot_info.robot_state<<endl;
															//	 cout<<"robot_info.robot_state="<<robot_info.robot_state<<endl;
																 robot_info.fsm_unlocked=false;
																 robot_info.ball_find=false;
															   }
											break;
							  case adjust_ball:

								  	  	  	  	  if(robot_info.ball_find==true)
								  	  	  	 {
								  	  	  	  		  time0=get_time();
								  	  	  		 robot_info.robot_state = round_goal;
								  	  	  	cout<<"head:"<<robot_info.robot_state<<endl;

								  	  	  	 }
								  	  	  	  	  else if((get_time()-time0)>8)
								  	  	  	  	  {

						//		  	  	  	  	 robot_info.ball_dis4robot = 50;
								  	  	  	  	robot_info.robot_state =search_ball;
								  	  	  	cout<<"head:"<<robot_info.robot_state<<endl;
								  	  	  	  	  }


								  	  	  break;
							  case round_goal:
							  	  	  	  	  	  	  {

														double Z= 6* PI / 180;
//														cout<<"angle="<<fabs((get_time()-time0)*Z-fabs(double(headangle))*PI/180)<<endl;
													  if(((get_time()-time0)*Z-fabs(double(headangle))*PI/180)>=0*PI/180)
															   {
					//									         robot_info.ball_dis4robot = 50;
																  robot_info.robot_state = approach_ball;
																  cout<<"head:"<<robot_info.robot_state<<endl;
																  time0=get_time();

																 }
							  	  	  	  	  	  	  	  }
											break;
							  case  approach_ball:
							  {
	//							  cout<<"time="<<get_time() - time0<<endl;
												  if( (get_time() - time0)>10)
													 {

													  	  	  	  	  	  	  if(robot_info.ball_find!=true)
																	 	 	 {
								//												   robot_info.ball_dis4robot = 50;
																				   robot_info.robot_state = search_ball;
																				   cout<<"head:"<<robot_info.robot_state<<endl;
																				 }
													  	  	  	  	  	  	  else
																			 {
																				   robot_info.robot_state = kick_ball;
																				   cout<<"head:"<<robot_info.robot_state<<endl;
																			 }
													 }


												  else  if(abs(int(robot_info.q0Real))<=20&&robot_info.ball_dis4robot <=DisMin)
													 {
																							 robot_info.robot_state = kick_ball;
																							 cout<<"head:"<<robot_info.robot_state<<endl;
													 }

							  }
										   break;

							  case  kick_ball:
								  	  	  	  	  	  	  	  	  	  if(robot_info.fsm_unlocked==true)
								  	  	  	  	  	  	  	  	  	  {
								  	  	  	  	  	  	  	  	  		  robot_info.robot_state = search_ball;
								  	  	  	  	  	  	  	cout<<"head:"<<robot_info.robot_state<<endl;
																		 robot_info.fsm_unlocked=false;
																		 robot_info.ball_find =false;
					//													 robot_info.ball_dis4robot = 50;

								  	  	  	  	  	  	  	  	  	  }
								  	  	  break;

							  case climb_up:

								                                if(robot_info.fall_info==0)
								                                {
								                                	delay_sec(0.5);
								                                	if(robot_info.fall_info==0)
								                                	{
								                                	robot_info.robot_state = search_ball;
								                                	cout<<"head:"<<robot_info.robot_state<<endl;
				//									  	  	  	  	 robot_info.ball_dis4robot = 50
								                               }
								                                }
								           break;



							  default:
										   break;
							}

					}

				usleep(1);
		}
return (void *)"fsm_change pthread finish.";
}
