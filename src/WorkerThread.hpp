#include <QThread>
#include <QTimer>

class WorkerThread : public QThread {
  Q_OBJECT
public:
  WorkerThread();
  virtual ~WorkerThread();

  void run() override;
  void setValue(QString path);

signals:
  void progressUpdated(int p, QString msg);

private:
  QString m_value;
};
