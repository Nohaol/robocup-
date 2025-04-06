/*
 * actions.cpp
 *
 *  Created on: 2014年9月17日
 *      Author: xuf
 */
#include "global.h"



//找球
void body_search(void)
{
	 time0=get_time();
	double lostTime = get_time()-time0;
	cout<<"body_search"<<endl;
	while(robot_info.robot_state == search_ball)
		    {
			       lostTime = get_time()-time0;// 当丢球时间大于一定值时，执行策略××× ToDo

			        if(lostTime<15)
                    		{
                   			updateOneStep(Vector3D(0.01, 0.0, 0));
                   			//cout<<"get it"<<endl;

                  		}
                   			else
                   	{
                     			updateOneStep(Vector3D(0.01,0.0,0));
                     			//cout<<"lost"<<endl;
                     		}

	    	}
}





//追球
int lostCount=0;
void body_chase(void)
{
	//	cout<<"body_chase"<<endl;

        double velChaseX = 0.03;
		double velChaseY =0.0;
		double velChaseZ =0; //6*PI/180;
		robot_info.calc_ball_info();
		while (robot_info.robot_state == chase_ball)
		                 {
		                 cout<<"chasing"<<endl;
                                       robot_info.calc_ball_info();
                                   //	cout<<"robot_info.ball_dis4robot="<<robot_info.ball_dis4robot<<endl;
                                       Vector3D velChase = Vector3D(0.03, 0.0, 0.000 );
                                     //			cout<<"ball_dis4robot="<<robot_info.ball_dis4robot<<endl;
                                     //			Vector3D velChase = Vector3D(0, -0.007, 0.0);
                           /*          			if(robot_info.ball_dis4robot<100)
		                             	{
			                        	velChase.X = 0.0075;
		                              	}
			                        else
			                          {
				                        velChase.X = 0.015;
			                              }*/
		                          	velChase.X = max(
					                                              min(velChaseX,  (robot_info.ball_dis4robot)/1500 * cos(((double) robot_info.q0Real *0.621* PI / 180))),  	0.0);
//                                          			cout<<"X = "<<velChase.X<<endl;

		                        	velChase.Y = max(
					                                               min(velChaseY,   (robot_info.ball_dis4robot )/1500 * sin(((double) robot_info.q0Real*0.621 * PI / 180))),    -velChaseY);
//                                         			cout<<"Y = "<<velChase.Y<<endl;
                                         			//cout<<""<<  (robot_info.ball_dis4robot )/850 * sin(((double) robot_info.q0Real * PI / 180))<<endl;

		                           	velChase.Z = max(min(velChaseZ, ((double) (robot_info.q0Real*0.621)) *0.5* PI / 180), -velChaseZ)/10;
//                                        			cout<<"Z = "<<velChase.Z<<endl;

		                            supportX = 0.018;




		                            	if (robot_info.q0Real > 20 || robot_info.q0Real < -20)
		                                             	{
		                            								velChase.Z=	0*robot_info.q0Real/abs(robot_info.q0Real);
		                            							//	cout<<"q0real="<<robot_info.q0Real<<endl;
				                                                   // cout<<"偏差过大  转身"<<endl;
				                                                     velChase.Y = 0.0;		//此时往后直走
				                                                     velChase.X = 0.03;
				                                                     cout<<"q0real"<<endl;

		                                              	}

	                                   //		cout << "速度	" << velChase.X << "   " << velChase.Y << "    " << velChase.Z * 180 / PI
	                                   //				<< "           " << robot_info.ball_dis4robot << "      " << qHead[1] << endl;
			                        updateOneStep(velChase);
                                    	//		cout<<"追球时行走"<<"距离"<<robot_info.ball_dis4robot<<endl;
                     	}
		supportX = 0.012;
		body_stop();

}







//根据航向角绕球
void body_round_yaw(void)//90对方球门，-90自己球门，180与-180处要注意
{
          cout<<"body_round_yaw"<<endl;
	      Vector3D velRound = Vector3D(0, 0.0, 0.0001 );
	     /*while( 1)
	      {
		         velRound.Z= 0.15* PI / 180;
		         velRound.Y=-velRound.Z*robot_info.ball_dis4robot/10;
		        updateOneStep(velRound);
	         }*/
	        //	robot_info.yaw=1.2*PI;
	    //  velRound.Z= 5* PI / 180;




	      //南球门（对着11出口）
	      if(robot_info.yaw_start<-40&&robot_info.yaw_start>-100)
	      {
									if(robot_info.yaw>-130.00&&robot_info.yaw<-15.00)
											 {
														velRound.Z=7* PI / 180;
													  //  velRound.Y=	-velRound.Z*robot_info.ball_dis4robot/1500;
													 velRound.Y =-0.03;
											}
								else if(robot_info.yaw>=-15.00&&robot_info.yaw<=15.00)
											{
													   velRound.Z=0;
														velRound.Y=0;
											}
								else
											{
													   velRound.Z= -7* PI / 180;
														// velRound.Y=-velRound.Z*robot_info.ball_dis4robot/1500;
													   velRound.Y =0.03;
											 }

									int i;
											for( i=0;i<5;i++)
											{
												updateOneStep(Vector3D(0,0.0,0.0001));
												cout<<"tabu"<<endl;
											}

								while(robot_info.robot_state == round_yaw)
											   {
														 robot_info.calc_ball_info();

															if(robot_info.yaw>-130.00&&robot_info.yaw<-15.00)
																{
																	if(robot_info.q0Real<-20)
																			{
																		cout<<"zguoda"<<endl;
																					velRound.Z=0;
																			}
																			else if(robot_info.q0Real>20)
																			{
																				cout<<"yguoda"<<endl;
																				velRound.Y=0;
																				velRound.Z= 7* PI / 180;
																			}
																			else
																			{
																				velRound.Z= 7* PI / 180;
																				//velRound.Y=-velRound.Z*robot_info.ball_dis4robot/1500;
																				 velRound.Y =-0.03;

																			}

																}
															else
																{
																	if(robot_info.q0Real>20)
																	{
																		cout<<"zguoda"<<endl;
																		velRound.Z=0;
																	}
																	else if(robot_info.q0Real<-20)
																	{
																		cout<<"yguoda"<<endl;
																		velRound.Z= -7* PI / 180;
																		velRound.Y=0;
																	}
																	else
																	{
																		velRound.Z= -7* PI / 180;
																		//velRound.Y=-velRound.Z*robot_info.ball_dis4robot/1500;
																		 velRound.Y =0.03;

																	}
																}


															supportX = 0.015;
													       updateOneStep0(velRound);
	                           }
	      }








	      						//北球门
	      else{

	      						   if(robot_info.yaw>15.00&&robot_info.yaw<130.00)
	      										     {
	      								                       	velRound.Z=-7* PI / 180;
	      										                velRound.Y=	0.03;
	      								          	}
	      								else if(robot_info.yaw>=-15.00&&robot_info.yaw<=15.00)
	      											{
	      											           velRound.Z=0;
	      											            velRound.Y=0;
	      											}
	      								else
	      									        {
	      									                   velRound.Z= 7* PI / 180;
	      											             velRound.Y=-0.03;
	      									         }

	      						          int i;
	      						          		for( i=0;i<5;i++)
	      						          		{
	      						          			updateOneStep(Vector3D(0,0.0,0.0001));
	      						          			cout<<"tabu"<<endl;
	      						          		}

	      								while(robot_info.robot_state == round_yaw)
	      						                     {

	      														 robot_info.calc_ball_info();
	      												if(robot_info.yaw>15.00&&robot_info.yaw<130.00)
	      												{
	      															if(robot_info.q0Real>30)
	      															{
	      																	velRound.Z=0;
	      															}
	      															else if(robot_info.q0Real<-30)
	      														{

	      															velRound.Z= -7* PI / 180;
	      															velRound.Y=0;
	      															}
	      														else
	      														{
	      															velRound.Z= -7* PI / 180;
	      															velRound.Y=0.03;

	      															}
	      												}





	      												else
	      													{
	      														if(robot_info.q0Real<-30)
	      																{
	      																		velRound.Z=0;
	      																}
	      																else if(robot_info.q0Real>30)
	      																{

	      																	velRound.Y=0;
	      																	velRound.Z= 7* PI / 180;
	      																}
	      																else
	      																{
	      																	velRound.Z= 7* PI / 180;
	      																	velRound.Y=-0.03;

	      																}

	      													}
	    												supportX = 0.015;
	    												updateOneStep0(velRound);
	      						                     }
										}

	      supportX = 0.012;
}








//根据球门绕球
void body_search_goal(void)
{

	body_stop();
   /*   while( robot_info.robot_state ==search_goal)
      {
	updateOneStep(Vector3D(0,0,0.0001));
      }*/
}


void body_adjust_ball(void)
{
	// cout<<"body_adjust_ball"<<endl;
	 body_stop();
	/*  while( robot_info.robot_state ==adjust_ball)
	      {

		  robot_info.calc_ball_info();
		updateOneStep(Vector3D(0,0,0.0001));
	      }*/
}//为什么要用bodystop函数？那样与上一个函数意义一样了.







//绕球
void body_round_goal(void)
{

	 cout<<"body_round_goal"<<endl;
	 robot_info.calc_ball_info();
	int i;
//	cout<<"headangle="<<headangle<<endl;
	Vector3D velRound = Vector3D(0.03, 0.0, 0.0001 );//直行
	if(headangle>0)
	{
	velRound.Z= 0.05;
	//cout<<"velRound.Z= "<<velRound.Z<<endl;
	}
	if(headangle<0)
	{
		velRound.Z= -0.05;
//		cout<<"velRound.Z= "<<velRound.Z<<endl;
		}

	for( i=0;i<5;i++)
	{
		updateOneStep(Vector3D(-0.015,0,0.000001));
		//cout<<"tabu"<<endl;
	}

	time0=get_time();
	velRound.Y=-velRound.Z*robot_info.ball_dis4robot/150;
	while(robot_info.robot_state == round_goal)
	{
		cout<<"body_round_goal"<<endl;
	if(headangle>0)
	{
		if(robot_info.q0Real>30)
		{
			velRound.Z= 0.05;
			velRound.Y=-0.025;
		}
		else if(robot_info.q0Real<-30)
		{
			velRound.Z=-0.05;

		}
		else
		{
			velRound.Z= 0.0;
			velRound.Y=-velRound.Z*robot_info.ball_dis4robot/150;

		}
	}


	else
	{
		if(robot_info.q0Real<-30)
				{
					velRound.Y=-0.025;
					velRound.Z= -0.05;

				}
				else if(robot_info.q0Real>30)
				{
					velRound.Z=0.05;

				}
				else
				{
					velRound.Z= 0.05;
					velRound.Y=-velRound.Z*robot_info.ball_dis4robot/150;

				}

	}
						supportX = 0.015;
						velRound.Y=-velRound.Y;//(根据绕球时候方向选择是否注释)
						updateOneStep(velRound);
				}
	  supportX = 0.012;
    }





void body_stop(void)
{

	update_still();
}






void body_approach_ball(void)
{
	//body_stop();
//		serial_flag=0;
		//delay_sec(0.5);
		cout<<" body_approach_ball"<<endl;
		 double velapproachX = 0.03;
		double velapproachY =0.0;

	Vector3D	velapproach = Vector3D(0, 0.0, 0 );
	robot_info.calc_ball_info();
//	cout<<"q0real="<<robot_info.q0Real<<endl;
while(robot_info.robot_state ==approach_ball&&robot_info.ball_find!=true)
{
	updateOneStep(Vector3D(-0.015,0,0.0000001));
}

	 while( robot_info.robot_state ==approach_ball&&robot_info.ball_find==true)
	 {
		 robot_info.calc_ball_info();
	//	cout<<"distance="<<robot_info.ball_dis4robot<<endl;
	//	cout<<"q0real="<<robot_info.q0Real<<endl;
	 if(abs(robot_info.q0Real)>=30)
	    				{
		 	 	 	 	 	 velapproach.X=-0.03;
	    				}
	 else
	 {
		 velapproach.X = max(
		 					              min(velapproachX,  (robot_info.ball_dis4robot-10)/1700 * cos(((double) robot_info.q0Real *0.621* PI / 180))),  	0.0);
	 }

	    velapproach.Y=max(
                min(velapproachY,   (robot_info.ball_dis4robot )/300 * sin(((double) robot_info.q0Real*0.621 * PI / 180))),    -velapproachY);
	  //  cout<<"当		前	 速	度	"<<velCurrent.X<<"   "<<velCurrent.Y<<"      "<<velCurrent.Z*180/PI<<endl;


	    updateOneStep(velapproach);
	    cout<< " robot_info.ball_dis4robot=" <<robot_info.ball_dis4robot<<endl;
	 }
}





void body_kick(void)
{
	while( robot_info.robot_state ==kick_ball)
	{
		cout<<"body_kick"<<endl;

		for(int i=0;i <20;i++)
		{
		updateOneStep(Vector3D(0.03, 0.0, 0.000 ));
		cout<<"kick"<<endl;
		}

    body_stop();
	 	for( int i=0;i<6;i++)
	{
		updateOneStep(Vector3D(-0.0,0,0.000001));
		//cout<<"tabu"<<endl;
	}
	 send_serial_flag = true;
	 delay_sec(0.5);
	 if(robot_info.q0Real>=0)
	 {
		 sendfile("left_step_kick1.txt");}
	 else if(robot_info.q0Real<0)
	 {
			 sendfile("right_step_kick1.txt");}
   robot_info.fsm_unlocked=true;
   delay_sec(0.2);
   send_serial_flag = false;
	 delay_sec(0.2);
  for( int i=0;i<5;i++)
	{
		updateOneStep(Vector3D(-0.0,0,0.000001));
		//cout<<"tabu"<<endl;
	}// body_stop();
   //delay_sec(2);
   robot_info.ball_dis4robot = 100;
	}
}


void body_climb_up(void)
{
	  if( robot_info.robot_state ==climb_up)
	{
					cout<<"climb_up"<<endl;
					send_serial_flag = true;
					delay_sec(0.5);

					 if(robot_info.fall_info==1)
					 {
						 delay_sec(0.5);
						 if(robot_info.fall_info==1){
							 	 cout<<"climb_up_front"<<endl;
					 sendfile("climb_up_front.txt");
						 }

					 }
					 else if(robot_info.fall_info==2)
					 {
						 delay_sec(0.5);
						 if(robot_info.fall_info==2)
                            {
						 cout<<"climb_up_back"<<endl;
						sendfile("turn_over.txt");
						delay_sec(0.2);
						 sendfile("climb_up_front.txt");
						 }
					 }

					 delay_sec(2);
					 if(robot_info.fall_info==0)
					 {
					 send_serial_flag = false;
					 cout<<"success"<<endl;
					 }

	}
	robot_info.fall_info=0;
}




