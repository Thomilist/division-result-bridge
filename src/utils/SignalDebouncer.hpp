#ifndef __SIGNALDEBOUNCER_H__
#define __SIGNALDEBOUNCER_H__

#include <functional>
#include <tuple>

#include <QObject>
#include <QTimer>

#include "../../lib/verdigris/wobjectdefs.h"

#include "ForwardDeclarations.hpp"

namespace divi
{
    template<typename ... Parameters>
    class SignalDebouncer : public QObject
    {
        W_OBJECT(SignalDebouncer)
        
        private:
            std::function<void(Parameters ...)> output;
            int delay;
            QTimer timer;
            std::tuple<Parameters ...> parameters;

        public:
            void input(Parameters ... a_parameters)
            {
                parameters = std::make_tuple(a_parameters ...);
                timer.start(delay);
                return;
            }
            W_SLOT(input)
            
            SignalDebouncer(
                std::function<void(Parameters ...)> a_output,
                int a_delay,
                QObject* a_parent = nullptr)
                : QObject(a_parent)
                , output(a_output)
                , delay(a_delay)
            {
                timer.setSingleShot(true);
                connect(&timer, &QTimer::timeout, [this]{ std::apply(this->output, this->parameters); });
            }

            ~SignalDebouncer()
            { }
    };
}

#include "../../lib/verdigris/wobjectimpl.h"
W_OBJECT_IMPL_INLINE(divi::SignalDebouncer<Parameters ...>, template<typename ... Parameters>)

#endif // __SIGNALDEBOUNCER_H__