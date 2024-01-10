#ifndef WALL_HPP
#define WALL_HPP
#include "fixed_model.h"

/**
 * \brief Class that represents wall on the map
 */

class CWall : public CFixed_Model
{
    public:
                        CWall           ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*         clone           ( ) const override;    
};

#endif
