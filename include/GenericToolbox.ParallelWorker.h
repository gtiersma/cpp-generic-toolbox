//
// Created by Nadrino on 25/06/2021.
//

#ifndef CPP_GENERIC_TOOLBOX_GENERICTOOLBOX_THREADPOOL_H
#define CPP_GENERIC_TOOLBOX_GENERICTOOLBOX_THREADPOOL_H

#include "GenericToolbox.h"
#include "GenericToolbox.Wrappers.h"

#include <map>
#include <mutex>
#include <future>
#include <vector>
#include <string>


// Classes : ParallelWorker
namespace GenericToolbox{

  ENUM_EXPANDER(
      ThreadStatus, 0,
      Stopped,
      Idle,
      Running
  )

  class ParallelWorker {

  public:
    inline ParallelWorker();
    inline virtual ~ParallelWorker();

    inline void reset();

    inline void setIsVerbose(bool isVerbose);
    inline void setCheckHardwareCurrency(bool checkHardwareCurrency);
    inline void setNThreads(int nThreads);
    inline void setCpuTimeSaverIsEnabled(bool cpuTimeSaverIsEnabled);

    inline void initialize();

    inline const std::vector<std::string> &getJobNameList() const;
    inline int getNThreads() const;

    inline void addJob(const std::string& jobName_, const std::function<void(int)>& function_); // int arg is supposed to be the thread id
    inline void setPostParallelJob(const std::string& jobName_, const std::function<void()>& function_);
    inline void setPreParallelJob(const std::string& jobName_, const std::function<void()>& function_);
    inline void runJob(const std::string& jobName_);
    inline void removeJob(const std::string& jobName_);

    inline void pauseParallelThreads();
    inline void unPauseParallelThreads();

  protected:
    inline void reStartThreads();
    inline void startThreads();
    inline void stopThreads();

  private:
    // Parameters
    bool _isVerbose_{true};
    bool _checkHardwareCurrency_{true};
    bool _cpuTimeSaverIsEnabled_{false};
    int _nThreads_{-1};

    // Internals
    bool _isInitialized_{false};
    bool _stopThreads_{false};
    bool _pauseThreads_{false};
    std::vector<std::future<void>> _threadsList_;
    std::vector<ThreadStatus> _threadStatusList_;
    std::vector<std::function<void(int)>> _jobFunctionList_;
    std::vector<std::function<void()>> _jobFunctionPostParallelList_;
    std::vector<std::function<void()>> _jobFunctionPreParallelList_;
    std::vector<std::string> _jobNameList_;
    std::vector<std::vector<bool>> _jobTriggerList_;

  };

}

#include "implementation/GenericToolbox.ParallelWorker.impl.h"

#endif //CPP_GENERIC_TOOLBOX_GENERICTOOLBOX_THREADPOOL_H
