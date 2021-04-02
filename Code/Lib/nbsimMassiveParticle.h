#ifndef nbsimMassiveParticel_h
#define nbsimMassiveParticle_h

#include "nbsimParticle.h"
#include <Eigen/Dense>
#include <memory>
#include <vector>
#include "nbsimWin32ExportHeader.h"


namespace nbsim
{

    class MassiveParticle: public Particle{

        public:
            MassiveParticle(Eigen::Vector3d Position, Eigen::Vector3d Velocity, double Mass);
            ~MassiveParticle();
            
            double getMu();
            void addAttractor(std::shared_ptr<MassiveParticle> attractor);
            void removeAttractor(std::shared_ptr<MassiveParticle> attractor);
            void calculateAcceleration();
            void integrateTimestep(const double& timestep);

        private:
            double Mass_;
            Eigen::Vector3d Acceleration_;
            std::vector<std::shared_ptr<MassiveParticle>> ListofParticles;
            


    };


} // end namespace

#endif


