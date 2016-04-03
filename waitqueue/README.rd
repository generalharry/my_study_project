wait_queue_head_t myqueue; //decloare

init_waitqueue_head(&myqueue); // init

DECLARE_WAIT_QUEUE_HEAD(myqueue); //declare & init myqueue


wait_event(myqueu, condition);
wait_event_interrutible(myqueue, condition);

wait_event_timeout(myqueue, condition, jiffies);
wait_event_interruptible_timeout(myqueue, condition, jiffies);


sleep_on(&myqueue);
interruptible_sleep_on(&myqueue);


wake_up(&myqueue);
wake_up_interruptible(&myqueue);


related struct
wait_queue_head_t
workqueue_struct
work_struct
timer_list
