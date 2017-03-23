#ifndef PROJET_QHANDPOINTERBUTTON_HPP
#define PROJET_QHANDPOINTERBUTTON_HPP


#include <QtWidgets/QPushButton>

class QHandPointerButton: public QPushButton {
    Q_OBJECT
public:
    QHandPointerButton(QWidget* parent = 0): QPushButton(parent) {
        setCursor(Qt::PointingHandCursor);
    }

    QHandPointerButton(const QString& text, QWidget* parent = 0): QPushButton(text, parent) {
        setCursor(Qt::PointingHandCursor);
    }

    QHandPointerButton(const QString& text, int width, int height, QWidget* parent = 0): QPushButton(text, parent) {
        setCursor(Qt::PointingHandCursor);
        setFixedSize(width, height);
    }

//    virtual ~QHandPointerButton() = default;
};


#endif //PROJET_QHANDPOINTERBUTTON_HPP
