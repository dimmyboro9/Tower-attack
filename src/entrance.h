#ifndef ENTRANCE_HPP
#define ENTRANCE_HPP
#include "fixed_model.h"

/**
 * \brief Class that represents entrance on the map
 *
 * \details It has:
 *          m_Number - number of entry;
 */

class CEntrance : public CFixed_Model
{
    public:
                    CEntrance       ( size_t num = 0 );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*     clone           ( ) const override;

        /**
         * \brief That method prints model's sign
         * 
         * \param[in] os Stream, where will be sign printed
         */
        void        print           ( ostream& os ) const override;

        /**
         * \brief That method returns entry number ( only if model is an entrance )
         * 
         * \return The size_t - number of entrance
         */
        size_t      get_num         ( ) const override;

    private:
        size_t      m_Number;
};

#endif
