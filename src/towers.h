#ifndef TOWERS_HPP
#define TOWERS_HPP
#include "non_fixed_model.h"

const size_t NUM_OF_TOWERS = 4;

/**
 * \brief Class that represents all towers on the map
 */

class CTower : public CNon_Fixed_Model
{
    public:
                        CTower          ( const string& name, char sign, size_t hp, size_t damage, size_t range );
        virtual         ~CTower         ( ) noexcept = default;
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        virtual CModel* clone           ( ) const override = 0;

        /**
         * \brief Method that prints all model's stats
         *
         * \param[in] os Stream, where will be sign printed
         */
        void            print_info      ( ostream& os ) const override;

};        

#endif
