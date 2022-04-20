/* 
 * Based on 
 * https://forum.qt.io/topic/115662/qintvalidator-for-unsigned-long-values
 * by 
 * https://forum.qt.io/user/vronin
 */
#ifndef UIV_H
#define UIV_H

#include <QValidator>
#include "gol_core.h"


class UIntValidator : public QValidator {
    Q_OBJECT
public:
    UIntValidator(NS_GoL::index minimum, NS_GoL::index maximum, QObject *parent = nullptr):QValidator(parent), m_min(minimum), m_max(maximum){}

    UIntValidator(QObject *parent = nullptr):UIntValidator(std::numeric_limits<NS_GoL::index>::min(), std::numeric_limits<NS_GoL::index>::max(), parent)
    {}
    NS_GoL::index bottom() const { return m_min; }
    NS_GoL::index top() const { return m_max; }
    void setBottom(NS_GoL::index minimum){
        if(m_min==minimum)
            return;
        m_min=minimum;
        changed();
    }
    void setTop(NS_GoL::index maximum){
        if(m_max==maximum)
            return;
        m_max=maximum;
        changed();
    }
    void setRange(NS_GoL::index minimum, NS_GoL::index maximum){
        setBottom(minimum);
        setTop(maximum);
    }
    QValidator::State validate(QString &input, int&) const override{
        bool convertOk=false;
        NS_GoL::index numInput = input.toUInt(&convertOk);
        if(!convertOk)
            return QValidator::Invalid;
        if(numInput<m_min)
            return QValidator::Intermediate;
        if(numInput>m_max)
            return QValidator::Invalid;
        return QValidator::Acceptable;
    }
    ~UIntValidator(){};
    void fixup(QString &input) const{};

private:
    NS_GoL::index m_min;
    NS_GoL::index m_max;
    
};

#endif 
