#include "widget/timer.h"
#include "log.h"
#include <list>
#include <vector>
#include "utils.h"

namespace purple{
        
    Timer::Timer(){
        time_ = currentTimeMillis();
    }

    Timer::~Timer(){
        if(!taskList_.empty()){
            clear();
        }
        Log::i("timer" , "~timer deconstructor");
    }

    //delay 毫秒后 执行
    int Timer::schedule(std::function<void(void *)> runnable,long long delay){
        auto resultTask = buildTimerTask(runnable , delay , TimerTaskType::Once);
        taskList_.push_back(resultTask);
        return resultTask->taskId;
    }

    int Timer::scheduleAtFixedRate(std::function<void(void *)> runnable ,long long period){
        auto resultTask = buildTimerTask(runnable , period , FixedRate);
        taskList_.push_back(resultTask);
        return resultTask->taskId;
    }

    //移除延时任务
    bool Timer::removeScheduleTask(int rmTaskId){
        std::list<std::shared_ptr<TimerTask>>::iterator removeIter;
        auto iter = taskList_.begin();
        bool isDelete = false;
        
        while(iter != taskList_.end()){
            std::shared_ptr<TimerTask> task = *iter;
            if(task->taskId == rmTaskId){
                taskList_.erase(iter);  
                isDelete = true;
                break;
            }
            iter++;
        }//end while
        return isDelete;
    }


    std::shared_ptr<TimerTask> Timer::buildTimerTask(std::function<void(void *)> runnable,long long delay ,TimerTaskType taskType){
        auto timeTask = std::make_shared<TimerTask>();

        timeTask->taskId = genTaskId();
        timeTask->shouldRunTime = currentTimeMillis() + delay;
        timeTask->delayTime = delay;
        timeTask->runnable = runnable;
        timeTask->type = taskType;
        return timeTask;
    }

    // 以固定时间 period 毫秒 执行

    //step a timestamp
    void Timer::trick(){
        time_ = currentTimeMillis();
        
        std::vector<std::list<std::shared_ptr<TimerTask>>::iterator> removeList;
        auto iter = taskList_.begin();
        while(iter != taskList_.end()){
            std::shared_ptr<TimerTask> task = *iter;
            if(time_ >= task->shouldRunTime){
                // Logi("timer" , "task id %d time tasktime %lld cur %lld" ,
                // task->taskId , task->shouldRunTime , time_);
                task->runnable(nullptr);
                if(task->type == Once){
                    removeList.push_back(iter);
                }else if(task->type == FixedRate){
                    task->shouldRunTime = currentTimeMillis() + task->delayTime;
                }
                // taskList_.erase(iter);
            }
            iter++;
        }//end while

        if(!removeList.empty()){
            for(auto iter : removeList){
                taskList_.erase(iter);
            }//end for each
        }
    }
        
    void Timer::clear(){
        idIndex_ = 0;
        taskList_.clear();
    }
}




