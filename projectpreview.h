// set minimum size
// set starting size
// size can grow or reduce based on parent widget
#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>

class ProjectPreview : public QWidget
{
    Q_OBJECT

public:
    ProjectPreview(QString project, QWidget* parent = nullptr);
    ~ProjectPreview();
};
#endif // PROJECTPREVIEW_H
