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
            void setPosition(Eigen::Vector3d position); // setter for get the value of private variables Position_
            void setVelocity(Eigen::Vector3d velocity); // setter for get the value of private variables Velocity_
            void integrateTimeStep(Eigen::Vector3d acceleration, double timestep);

        private:
            Eigen::Vector3d Position_;
            Eigen::Vector3d Velocity_;

    };


} // end namespace

#endif
