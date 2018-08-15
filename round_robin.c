#include<stdio.h>
int main()
{
	struct datab{
		int pid,at,bt,st,rt;// structure to store the user input
		//at stores arrival time
		//bt stores brust time
		//st stores starting time 
		//rt stores remaining time after each context switching 
	};
	int p,atat=0,awt=0,tc=0,time=0;//initilize atat ,awt,tc,time to zero 
	printf("Enter no:of process : ");
	scanf("%d",&p);//read no:of process from the user
	struct datab db[p],temp;//creating object of structure
	//temp is to swap process during context switching
	for(int i=0;i<p;i++)
	{
		printf("Enter arrival time, brust time : ");
		scanf("%d%d",&db[i].at,&db[i].bt);//read input from user arrival and brust time
		db[i].rt=db[i].bt;//stating remaining time and burst time are equal 
		db[i].pid=i+1;//process id
	}
	printf("Enter time slice : ");
	scanf("%d",&tc);//read time quantum
	for(int ii=0;ii<p-1;ii++)//loop to arrange all arrival times in sorted order 
	{
		int i=0;
		while(i<p-1)
		{
			if(db[i].at>db[i+1].at)//it checks if arrival time of current procces is high then next 
			//one it swaps that procces to current position
			{
				//this is the swap function
				temp=db[i];
				db[i]=db[i+1];
				db[i+1]=temp;		
			}
			i++;
		}
	}
	time=db[0].at;
	printf("pid	at	bt	st	ct	tat	wt\n");
	int in=0,ss=0;
	//actival function of roundrobin algorithm begins
	int swit=0;
	while(in!=p)//this while loop will iterates until all processes complete its execution
	{
		
		for(int i=0;i<p;i++)
		{
		 	if(ss<=0)
		 	{
		 		//this block of code is for first process that comes for execution
		 		db[i].rt=db[i].rt-tc;
		 		time+=tc;//this process executes for the time quantion that give to it so time increments;
		 		//time +=tc is time + time quantum initially time=0;if time quantam is 2 ;now the time will be 0+2;
		 		db[i].st=db[i].at;	//the starting time of first process is time when it arrived
				ss++;//increments ss, so that the if condition wont be satified to run this block again
				i--;//decrement i to start again from first;
			}
			else
			{
				if(db[i+1].at<=time&&db[i].rt>0)//check if arrival time is less than time
				//and the remaining time of exection of the should be greater than zero to add 
				//the process into the process queue
				//this block of code arranges the process in the way they need to be executed
				//it places the process that should be executed next in first position
				//and places the executed process to last;
				{
					if(db[i].rt==db[i+1].at&&db[i+1].bt==db[i+1].rt)
					{
						/*this condition checks if a tie occurs between any process and do noting if 
						it occurs because when tie occurs the new process will be add last and old process add first into the queue
						*/
					}
					else
					{
						//this simple swap commands will swap the processes in the sturcture
						//this will be continuously repeated each time a context switching occurs
						temp=db[i];
						db[i]=db[i+1];
						db[i+1]=temp;
						swit++;
					}
				}
			}		
		}
		for(int i=in;i<in+1;i++)//this loop used to execute the first process in the structural array
		//if a process complets the "in" value increments and that process will not be distrubed
		{
			if(db[i].at<=time&&db[i].rt>tc)//checks if arrival time of process greater than time and 
			//remaning time is greater than time quantum 
			{
				if(db[i].bt==db[i].rt)//check if the process comes to execution for the first time
				{
		 			db[i].st=time;
		 			/*so the starting time of the process is time when it comes for execution
					 */
		 		}
				db[i].rt=db[i].rt-tc;//the process executed for time quation that given to it so the remainging time of 
				//process will be decremented by time quantum 
		 		time+=tc;//increment the time 
			}
			else if(db[i].at<=time&&db[i].rt<=tc)//checks if the remaining time is less than or equal to  time quantum
			{
				if(db[i].bt==db[i].rt)//this is to check if came for exection for first time some process brust time will be less or equal to time quantum
				{
		 			db[i].st=time;
		 		}
				time=time+db[i].rt;//increments the time by the remaining time of the process 
				//here i am not using time quantum to increment time because if the process remaing time might be less than time quantum 
				db[i].rt=0;//set the remaining time of the process to zero 
				in++;
				/*
				why i am incrementing "in" value
				p1 process completes it execution so it should not  come into execution again if
				"in"->=0 it points to p1 after incremented  "in"->1
				so it points to the process in index 1 and wont select it again
				each time "in" increments a will completes its execution
				p1[0] 
				p2[1]<-"in"
				p3[2]
				p4[3]					
				
				
				
				*/
				int tat=(time-db[i].at);//calculate the turnaround time of process that completes its execution
				int wt=tat-db[i].bt;//calculate wating time
				atat+=tat;//total turnaround time of all process
				awt+=wt;	
				printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",db[i].pid,db[i].at,db[i].bt,db[i].st,time,tat,wt);//as you know it prints the result
			}
			else
			{
					/*for example p1 arrival time is 0 and burst time is 10
		p2 at is 5 and bt is 5
		p3 at is 7 and bt is 7
		p4 at is 50 and bt is 2
		p4 does comes to ready state until the time is 50 so time will go on incrementing until all the process 
		comes and finish its execution*/
				time+=tc;
			}
	
	 	}
	}
	printf("Context switchings : %d\n",swit);
	printf("Average turnaround time : %.2f\n",(float)atat/p);//calculate average turnaround time
	printf("Average waiting time : %.2f\n",(float)awt/p);//calculate average waiting time
	/*
	if there are any errors sorry ,i am beginner so please excuse me.
											Thank You
	*/
}
