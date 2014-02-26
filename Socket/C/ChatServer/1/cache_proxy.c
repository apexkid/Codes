#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<netdb.h>
#define buf_size 1000000
#define max_len 100

int response_num;

struct cach_mem
{
char cont[60000];
};

struct all_request
{
  int count;
  char cont[60000];
};

struct all_request reqs[50];
struct cach_mem address[50];
struct cach_mem resp[50];

int req_count=0;         //track all request.

int check_history(char* nam, int lim)
{ int i;
printf("\nChecking for the History of: %s\n\n",nam);
for (i=1; i<=lim; i++)
	{if (strcmp(address[i].cont,nam)==0)
	{printf("\n Requested Page found in the History");
	response_num=i;
	return i;}
	
	}
return 0;
}

parse_URL(char *url, char *hostname, int *port, char *identifier)
{
    char protocol[max_len], scratch[max_len], *ptr=0, *nptr=0;
    printf("url is %s",url);
    strcpy(scratch, url);
    ptr = (char *)strchr(scratch, ':');//strchr will give pointer to the position of ":"
    if (!ptr)
    {
	fprintf(stderr, "Wrong url: no protocol specified\n");
	exit(1);
    }
    strcpy(ptr, "\0");
    strcpy(protocol, scratch);
    if (strcmp(protocol, "GET http"))//protocol contains everything before ":"
    {
	fprintf(stderr, "Wrong protocol: %s\n", protocol);
    }

    strcpy(scratch, url);
    ptr = (char *)strstr(scratch, "//");//strstr will give pointer to position of substring "//"
    if (!ptr)
    {
	fprintf(stderr, "Wrong url: no server specified\n");
	exit(1);
    }
    ptr += 2;
    
    char *temp=0;
    
    strcpy(hostname,ptr);
    hostname=strtok(hostname," ");
        
    nptr = (char *)strchr(ptr, ':');
//checking whether port no is specified,if not given we set it to 80 by default
    if (!nptr)
    {
	*port = 80; 
	nptr = (char *)strchr(hostname, '/');
    }
    else
    {	
	sscanf(nptr, ":%d", port);
	nptr = (char *)strchr(hostname, ':');
    }

    if (nptr)
      *nptr = '\0';

    nptr = (char *)strchr(ptr, '/');
    
	if (!nptr)
    {
	fprintf(stderr, "Wrong url: no file specified\n");
	exit(1);
    }
    
    strcpy(identifier, nptr);
}


int main(int argc,char* argv[])
{
	int url_num=0;
        FILE *file,*fp,*fp1;
	
	int j;
	for(j=0;j<50;j++)    //initialize counter
	   reqs[j].count=0;

	int sockfd,clientfd,i,serverfd,rc;
	int bi;
         char *url=0;
         char hostname[max_len],identifier[max_len];
	char content[100]="\0";
         int port,myport;
        char buf[100],x[200];
        char *request=0;
          request=x;
        url=buf;
	if (argc<2)
	 {fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
	 }
	myport=atoi(argv[1]);
	struct sockaddr_in serv_addr,cl_addr,rserv_addr;
	if((sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
	{
		perror("socket");
		exit(1);
	}
         char BUFFER[buf_size];
       
         struct hostent *h;
	bzero((char*)&serv_addr,sizeof(serv_addr));
	printf("\nPORT ADDRESS IS :%d\n",myport);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);


		bi=bind(sockfd,((struct sockaddr *)&serv_addr),sizeof(serv_addr));
	if(bi==-1)
	{
		perror("bind");
		exit(1);
	}
	i=sizeof(cl_addr);
	socklen_t t;
	t=sizeof(struct sockaddr_in);
	listen(sockfd,i);
	printf("\n\t\t\t\t--------------\n\t\t\t\t PROXY SERVER\n\t\t\t\t--------------\n");
        while(1)
        {         
        	printf("Waiting for the connection\n\n");
		    clientfd=accept(sockfd,(struct sockaddr *)&cl_addr,&t);
		  if(clientfd==-1)
		  {	
			  printf("\nCheck description parameters\n");
			  goto exit;
		  }
		  printf("\n\t\tConnection Established(client accepted)From :%d\n",inet_ntoa(cl_addr.sin_addr));      
		 
		  i=recv(clientfd,content,40,0);
                 strcpy(url,"");
                 url=(char *)strcat(url,content);
              
if (check_history(url, url_num)==0)
{       
  printf("Request not in cache.Getting from server...");
  int flag=0;
  for(j=0;j<req_count;j++) 
  {
     if(strcmp(reqs[j].cont,url)==0)
       {
         reqs[j].count++;
         flag=1;
         break;
       }
  } 
  if(flag==0)
  {
    strcpy(reqs[req_count].cont,url);
    reqs[req_count].count=1;
    req_count++;
  }
 printf("Request count %d",reqs[j].count);                 
if(reqs[j].count>=5)
{
     if (url_num==50) url_num=1;
	else url_num++;
	strcpy(address[url_num].cont,url);
}
	printf("\n\nThis is the content:%s\n\n",address[url_num].cont);
       
                 parse_URL(url,hostname,&port,identifier);
                  
               
                 printf("\nUSER IS REQUESTING FOR FOLLOWING: \n\t--Hostname =  %s    Port = %d   Identifier =  %s\n",hostname,port,identifier);
                 
                 
                 
                 
                 h=gethostbyname(hostname);
                 if(h==NULL)
                    {
                      printf("Unknown host :%s",hostname);
                       goto exit;
                    }
                   
                   rserv_addr.sin_family=h->h_addrtype;
                   memcpy((char *) &rserv_addr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
                   rserv_addr.sin_port=htons(port);
                  
                    serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd<0) 
	{
		perror("cannot open socket ");
		goto exit;
	}

	
	printf("Bind port number...  ");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(0);
  
	rc = bind(serverfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
            if(rc<0) 
	       {
		printf(" cannot bind port TCP %u\n",port);
		perror("error ");
		exit(1);
	       }
         printf("Connect to server...\n");
	rc = connect(serverfd, (struct sockaddr *) &rserv_addr, sizeof(rserv_addr));
	if(rc<0) 
	{
		perror("cannot connect ");
		goto exit;
	}       
                    strcpy(request,"GET ");
                    strcpy(request,"GET / HTTP/1.0\r\nHOST:");
                    request=(char *)strcat(request,hostname);
                    request = (char *)strcat( request, "\r\n");
                    request=(char *)strcat(request,"Connection: Close\r\n");
                    request = (char *)strcat( request, "\r\n");
                    request = (char *)strcat( request, "\r\n");
                   printf("Sending the request to the remote server :\n %s",request);
                    if(write(serverfd,request,strlen(request))==-1)
                       {
                          perror("can't send the request");
                       }
                     bzero(BUFFER,buf_size);
                   
                     printf("      Sending the desired response.....\n ");
                     file=fopen("web.html","w+");
                    do
   	               { rc=0;
		         bzero(BUFFER,buf_size);    
    	                 rc = read(serverfd, BUFFER, buf_size);
		         if( rc > 0)
		             { 
		                 printf("%s",BUFFER);
                                 fprintf(file,"%s",BUFFER);
			        write(clientfd,BUFFER,buf_size);
			        if(reqs[j].count>=5)
  					strcat(resp[url_num].cont,BUFFER);
                             }
                    	}while(rc>0);
                    fclose(file);
                    fp1=fopen("web.html","r");
                    fp=fopen("temp.html","w");
                    int copy_check=0;
                    char str[200];
                    while(fscanf(fp1,"%s",str)!=EOF)
 		   {
 		      printf("read from file %s\n",str);
 		      if(strncmp(str,"<HTML>",6)==0)
 		       copy_check=1;
 		      if(copy_check==1)
 		       fprintf(fp,"%s",str);
                   } 
                   remove("web.html");
                   rename("temp.html","web.html");
                   fclose(fp);
                   fclose(fp1);
                   
                   
                   printf("\nResponse is sent");
         exit:        close(serverfd);
		  bzero(content,sizeof content);
                   bzero(BUFFER,buf_size); 
		  close(clientfd);  
}

else 

{//response_num=check_history(url, url_num);
	//write(clientfd, "\nRetrieving from cache\n",strlen("\nRetrieving from cache\n")
	printf("\n\tretrieving from cache");
	send(clientfd,resp[response_num].cont,strlen(resp[response_num].cont),0);
	printf("\t\n\tsent from cache");
bzero(content,sizeof content);
close(clientfd);
	
}
                   printf("\n\t\t\t\t------------------------------\n\t\t\t\t      End of a session \n\t\t\t\t------------------------------\n\n");
                    
                    
        }
	return(0);
}
