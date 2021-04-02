#ifndef nbsimParticle_h
#define nbsimParticle_h


#include "nbsimWin32ExportHeader.h"
#include <Eigen/Dense>

namespace nbsim
{

    class Particle{

        public:
            Particle(Eigen::Vector3d Position, Eigen::Vector3d Velocity);
            ~Particle();
            Eigen::Vector3d getPosition() const;
            Eigen::Vector3d getVelocity() const;
            void integrateTimeStep(Eigen::Vector3d acceleration, double timestep);

        protected:
            Eigen::Vector3d Position_;
            Eigen::Vector3d Velocity_;

    };


} // end namespace

#endif
