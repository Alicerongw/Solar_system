#ifndef nbsimParticle_h
#define nbsimParticle_h

#include <Eigen/Dense>
#include "nbsimWin32ExportHeader.h"


namespace nbsim
{

    class Particle{

        public:
            Particle(Eigen::Vector3d Position, Eigen::Vector3d Velocity);
            ~Particle();
            Eigen::Vector3d getPostion() const;
            Eigen::Vector3d getVelocity() const;
            void integrateTimeStep(Eigen::Vector3d acceleration, double timestep);

        private:
            Eigen::Vector3d Position_;
            Eigen::Vector3d Velocity_;

    };


} // end namespace

#endif
