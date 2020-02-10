#ifndef H_SEM_H
#define H_SEM_H

extern int creat_or_get_sem(int nsems);
extern void init_sem(int semid, int semnum, int val);
extern void del_sem(int semid);
extern void p_sem(int semid, int semnum_buf[], int nsops);
extern void v_sem(int semid, int semnum_buf[], int nsops);

#endif



