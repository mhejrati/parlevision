#include "LibraryElement.h"

#include <QtGui>

#include "RefPtr.h"
#include "PipelineElement.h"
#include "Pin.h"

using namespace plv;
using namespace plvgui;

LibraryElement::LibraryElement(RefPtr<PipelineElement> element, QWidget* parent)
    : QWidget(parent),
    element(element)
{
    QSizePolicy sp = QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sp.setHeightForWidth(true);
    this->setSizePolicy(sp);
    this->setContentsMargins(0,0,0,0);

//    this->setMinimumSize(100,40);
//    this->setMaximumSize(100,40);
//        this->adjustSize();
//    this->resize(100,40);
//    this->setFixedHeight(40);

    this->setObjectName("Library Element " + element->getName());

    this->outerContainer = new QVBoxLayout(this);
    this->outerContainer->setAlignment(Qt::AlignCenter);
    this->outerContainer->setContentsMargins(8,8,8,8);

    QWidget* pinWrapper = new QWidget(this);

    this->innerContainer = new QHBoxLayout(pinWrapper);
    this->innerContainer->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    this->innerContainer->setContentsMargins(0,0,0,0);
    QWidget* inPinWrapper = new QWidget(this);

    this->inPinContainer = new QVBoxLayout(inPinWrapper);
    this->inPinContainer->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->inPinContainer->setContentsMargins(0,0,0,0);
    QWidget* outPinWrapper = new QWidget(this);

    this->outPinContainer = new QVBoxLayout(outPinWrapper);
    this->outPinContainer->setAlignment(Qt::AlignTop | Qt::AlignRight);
    this->outPinContainer->setContentsMargins(0,0,0,0);

    this->innerContainer->addWidget(inPinWrapper, Qt::AlignLeft | Qt::AlignTop);
    this->innerContainer->addWidget(outPinWrapper, Qt::AlignRight | Qt::AlignTop);

    QLabel* title = new QLabel(this->element->getName(), this);
    title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->outerContainer->addWidget(title, Qt::AlignCenter);
    this->outerContainer->addWidget(pinWrapper);

    const PipelineElement::InputPinMap& inPins = element->getInputPins();
    for( PipelineElement::InputPinMap::const_iterator itr = inPins.begin()
        ; itr!=inPins.end(); ++itr)
    {
        RefPtr<IInputPin> pin = itr->second;
        assert(pin.isNotNull());
        QWidget* label = new QLabel(pin->getName());
        label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        inPinContainer->addWidget(label, Qt::AlignLeft | Qt::AlignTop);
    }

    const PipelineElement::OutputPinMap& outPins = element->getOutputPins();
    for( PipelineElement::OutputPinMap::const_iterator itr = outPins.begin()
        ; itr!=outPins.end(); ++itr)
    {
        RefPtr<IOutputPin> pin = itr->second;
        assert(pin.isNotNull());
        QWidget* label = new QLabel(pin->getName());
        label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        outPinContainer->addWidget(label, Qt::AlignRight | Qt::AlignTop);
    }

    this->setBackgroundRole(QPalette::Base);
    repaint();
}

void LibraryElement::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPainterPath path;
    painter.setRenderHint(QPainter::Antialiasing);
    path.addRoundedRect(0, 0, this->width()-1, this->height()-1, 8.0, 8.0);
    painter.fillPath(path, Qt::green);
    painter.strokePath(path, painter.pen());
    QWidget::paintEvent(event);
}

QSize LibraryElement::sizeHint() const
{
//    return QSize(100,40);
    return QWidget::sizeHint();
}

int LibraryElement::heightForWidth(int w) const
{
    return QWidget::heightForWidth(w);
}

void LibraryElement::mousePressEvent(QMouseEvent*)
{
    emit(pressed());
}

void LibraryElement::mouseMoveEvent(QMouseEvent*)
{
    emit(moved());
}

void LibraryElement::mouseReleaseEvent(QMouseEvent*)
{
    emit(released());
}
