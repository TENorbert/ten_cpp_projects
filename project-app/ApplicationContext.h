#ifndef AQUAGATOR_CONTEXT_H
#define AQUAGATOR_CONTEXT_H

#include "GarfunkelData.h"
#include "GarfunkelIPCData.h"

#include "ecolab.h"
#include "esignals.h"

namespace Garfunkel
{
    class TerminateGarfunkel : public ecolab::Signals::IHandler
    {
       public:
        
            //  From ecolab::Signals::HandlerT
        
            /*!
                \brief  Method that is called to handle the TERM signal.
                
                Method that is called to handle the TERM signal. The signal is
                handled by terminating the signal-processing thread.
                
                \param[in]  None
                
                \param[out] None
                
                \return     None
                
                \throw      None
            */
            virtual void operator()() 
            {  
            	GarfunkelData & GarfunkelData = GarfunkelData::Instance();
				std::cout << "Received a termination signal" << std::endl;
				GarfunkelData._continueRunning.Set(False);
            }


    };
    

    static ecolab::Shareable< BOOLEAN > ContinueProcessing(True);

    class SignalHandler : public ecolab::Signals::IHandler
    {
        public:

            SignalHandler(){};
            virtual ~SignalHandler(){};

            //  From ecolab::Signals::HandlerT

            /*!
            */
            virtual void operator()()
            {
                /*
                SIGTERM or SIGINT was received.  Set a flag to gracefully shut down the application.
                */
                std::cout << "Stop Command Received... shutting down" << std::endl;
                ContinueProcessing.Set(False);
            }
    };



};


#endif
