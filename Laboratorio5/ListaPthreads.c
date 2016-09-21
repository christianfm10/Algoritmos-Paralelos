#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
double timeval_diff(struct timeval *a, struct timeval *b)
{
 return
   (double)(a->tv_sec + (double)a->tv_usec/1000000) -
   (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
struct list_node *head_p;

int Member3(int value){
    struct list_node *temp_p;
    pthread_mutex_lock(&head_p_mutex);
    temp_p = head_p;
    while(temp_p != NULL && temp_p->data < value){
        if(temp_p->next != NULL)
            pthread_mutex_lock(&(temp_p->next->mutex));
        if(temp_p == head_p)
            pthread_mutex_unlock(&head_p_mutex);
        pthread_mutex_unlock(&(temp_p->mutex));
        temp_p = temp_p->next;
    }
    if(temp_p == NULL || temp_p->data >value){
        if(temp_p == head_p)
            pthread_mutex_unlock(&head_p_mutex);
        if(temp_p != NULL)
            pthread_mutex_unlock(&(temp_p->mutex));
        return 0;

    }else{
        if(temp_p == head_p)
            pthread_mutex_unlock(&head_p_mutex);
        pthread_mutex_unlock(&(temp_p->mutex));
        return 1;


    }


}
int Insert2(int value){
    struct list_node* curr_p=head_p;
    struct list_node* pred_p=NULL;
    struct list_node* temp_p;
    while(curr_p !=  NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(struct list_node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if(pred_p == NULL)
            head_p = temp_p;
        else
            pred_p->next=temp_p;
        return 1;
    }else{
        return 0;
    }
}
int Member(int value,struct list_node* head_p){z
    struct list_node *curr_p = head_p;
    while(curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;
    if(curr_p == NULL || curr_p->data>value){
        return 0;
    }else{
        return 1;
    }
}

int Insert(int value,struct list_node **head_p){
    struct list_node* curr_p=*head_p;
    struct list_node* pred_p=NULL;
    struct list_node* temp_p;
    while(curr_p !=  NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(struct list_node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if(pred_p == NULL)
            *head_p = temp_p;
        else
            pred_p->next=temp_p;
        return 1;
    }else{
        return 0;
    }
}
int Delete(int value,struct list_node **head_p){
    struct list_node* curr_p=*head_p;
    struct list_node* pred_p=NULL;
    while(curr_p != NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p != NULL && curr_p->data == value){
        if(pred_p == NULL){
            *head_p = curr_p->next;
            free(curr_p);
        }else{
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;

    }else{
        return 0;



    }
}
void Mostrar(){

    struct list_node *curr_p = head_p->next;
    while(curr_p != NULL){
       printf("%d ",curr_p->data);
       curr_p = curr_p->next;}

}

int Member2(int value){

    struct list_node *curr_p = head_p;
    while(curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if(curr_p == NULL || curr_p->data>value){
        return 0;
    }else{
        return 1;
    }
}
int Insert2(int value){
    struct list_node* curr_p=head_p;
    struct list_node* pred_p=NULL;
    struct list_node* temp_p;
    while(curr_p !=  NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(struct list_node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if(pred_p == NULL)
            head_p = temp_p;
        else
            pred_p->next=temp_p;
        return 1;
    }else{
        return 0;
    }
}
int Delete2(int value){
    struct list_node* curr_p=head_p;
    struct list_node* pred_p=NULL;
    while(curr_p != NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p != NULL && curr_p->data == value){
        if(pred_p == NULL){
            head_p = curr_p->next;
            free(curr_p);
        }else{
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;

    }else{
        return 0;



    }
}
void* MemberV(void *value ){
	//rwlock_rdlock(&t);
      //  pthread_rwlock_rdlock(&lock);
	//pthread_mutex_lock(&head_p_mutex);
   // printf("%d",M	ember2((int)value));
	Member3((int)value);
	//pthread_mutex_unlock(&head_p_mutex);
      //  pthread_rwlock_unlock(&lock);
	//rwlock_rdunlock(&t);

//    return;

}
void* InsertV(void *value ){
	pthread_mutex_lock(&head_p_mutex);
//              pthread_rwlock_wrlock(&lock);
               Insert2((int)value);
//    printf("%d",Insert2((int)value));
//              pthread_rwlock_unlock(&lock);
	pthread_mutex_unlock(&head_p_mutex);

 //   return;

}
void* DeleteV(void *value ){
	pthread_mutex_lock(&head_p_mutex);
//    pthread_rwlock_wrlock(&lock);
    Delete2((int)value);
//    pthread_rwlock_unlock(&lock);
	pthread_mutex_unlock(&head_p_mutex);
//    return;

}

int main(int argc, char *argv[])
{

    pthread_t *thread_handles;
    thread_count = strtol(argv[1],NULL,10);
    thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
    pthread_rwlock_init(&lock,NULL);

    int lista[1000];
    for(int i=0;i<1000;i++){
        lista[i]=rand()%100000;
	//printf("%d \n",lista[i]);
}
    for(int i=0;i<1000;){
	    for(thread=0;thread<thread_count;thread++,i++){
		pthread_create(&thread_handles[thread],NULL,InsertV,(void*)lista[i]);

		}
	    for(thread=0;thread< thread_count;thread++)
		pthread_join(thread_handles[thread],NULL);

}
  //  Mostrar();
    gettimeofday(&t_ini, NULL);	
    for(int i=0;i<80000;){
        for(thread=0;thread<thread_count;thread++,i++){
             pthread_create(&thread_handles[thread],NULL,MemberV,(void*)(rand()%100000));

        }
        for(thread=0;thread< thread_count;thread++)
             pthread_join(thread_handles[thread],NULL);
}
    for(int i=0;i<10000;){
        for(thread=0;thread<thread_count;thread++,i++){
             pthread_create(&thread_handles[thread],NULL,InsertV,(void*)(rand()%100000));

        }
        for(thread=0;thread< thread_count;thread++)
             pthread_join(thread_handles[thread],NULL);
}
    for(int i=0;i<10000;){
        for(thread=0;thread<thread_count;thread++,i++){
             pthread_create(&thread_handles[thread],NULL,DeleteV,(void*)(rand()%100000));

        }
        for(thread=0;thread< thread_count;thread++)
             pthread_join(thread_handles[thread],NULL);
}
    gettimeofday(&t_fin, NULL);	

    secs = timeval_diff(&t_fin, &t_ini);
    printf("\n %.16g milliseconds\n", secs * 1000.0);
    free(thread_handles);
    return 0;
}
