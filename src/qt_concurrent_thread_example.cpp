
#include <QGuiApplication>
#include <QtConcurrent>
#include <filesystem>
#include <iostream>
#include <vector>

std::vector<std::string> exsitingfiles;

template <typename T> void printArray(T array) {
  for (const auto &element : array)
    std::cout << element << std::endl;
}

void uploader(const std::string &file) {
  qDebug() << "uploading file: " << file.c_str() << " in thread "
           << QThread::currentThread();

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::filesystem::remove("outbox/" + file);
}

void importer(const std::string &file) {

  qDebug() << "importing file: " << file.c_str() << " in thread "
           << QThread::currentThread();
  std::filesystem::create_directories("outbox/" + file);
  // std::filesystem::create_directories("outbox/" + file + "_");

  std::this_thread::sleep_for(std::chrono::seconds(4));

  QtConcurrent::run(QThreadPool::globalInstance(), [=]() { uploader(file); });
}

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  exsitingfiles = {"file1", "file2", "file3", "file4"};

  for (const auto &file : exsitingfiles) {
    qDebug() << "creating: " << file.c_str();
    std::filesystem::create_directories("outbox/" + file);
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));

  for (const auto &file : exsitingfiles) {
    qDebug() << "uploading " << file.c_str() << " in thread "
             << QThread::currentThread();
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() { uploader(file); });
  }

  std::vector<std::string> newfiles = {"newfile1", "newfile2", "newfile3",
                                       "newfile4"};

  // QFutureWatcher<int> watcher;
  // connect(&watcher, &QFutureWatcher<int>::finished, &myObject,
  // &MyClass::handleFinished);

  for (const auto &file : newfiles) {
    qDebug() << file.c_str() << " from " << QThread::currentThread();
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() { importer(file); });
  }

  // std::this_thread::sleep_for(std::chrono::minutes(5));

  // QObject::connect(reply, &QNetworkReply::finished, &firstRequestLoop, [&]()
  // { firstRequestLoop.exit(0); });

  return app.exec();
}
