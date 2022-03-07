#include "job_manager2.h"

#include <QCoreApplication>
#include <unistd.h>


void test()
{
    qInfo() << "test//////////////////////////////////////////////////////////";
    sleep(30);
    auto lambda = []()
    {
        qInfo() << "lambda" << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
        sleep(10);
        qInfo() << "lambda" << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    };
    lambda();

    // Job* job = new Job;
    // job->func = lambda;
    
    // job->start();
    // while (!job->isFinished()){};
    // delete job;
}

auto lambda = []()
{
    qInfo() << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    sleep(30);
    qInfo() << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "main thread : " << QThread::currentThreadId();

    // test();
    JobManager2 jobManager;
    jobManager.jobs["test"] = new Job2;
    jobManager.jobs["test"]->func = lambda;

    jobManager.jobs["test2"] = new Job2;
    jobManager.jobs["test2"]->func = test;
    QObject::connect(jobManager.jobs["test"], SIGNAL(finished()), &jobManager, SLOT(removeJob()));
    QObject::connect(jobManager.jobs["test2"], SIGNAL(finished()), &jobManager, SLOT(removeJob()));
    jobManager.jobs["test"]->start();
    jobManager.jobs["test2"]->start();

    qInfo() << "main" << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    qInfo() << "main thread : " << QThread::currentThreadId();

    return a.exec();
}