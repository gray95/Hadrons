/*
 * Test_field_io.cpp, part of Hadrons (https://github.com/aportelli/Hadrons)
 *
 * Copyright (C) 2015 - 2023
 *
 * Author: Antonin Portelli <antonin.portelli@me.com>
 *
 * Hadrons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hadrons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hadrons.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See the full license in the file "LICENSE" in the top level distribution 
 * directory.
 */

/*  END LEGAL */
#include <Hadrons/Modules.hpp>
#include <Hadrons/Application.hpp>

using namespace Grid;
using namespace Hadrons;

int main(int argc, char *argv[])
{
    // initialization //////////////////////////////////////////////////////////
    Grid_init(&argc, &argv);
    HadronsLogError.Active(GridLogError.isActive());
    HadronsLogWarning.Active(GridLogWarning.isActive());
    HadronsLogMessage.Active(GridLogMessage.isActive());
    HadronsLogIterative.Active(GridLogIterative.isActive());
    HadronsLogDebug.Active(GridLogDebug.isActive());
    LOG(Message) << "Grid initialized" << std::endl;

    Application            application;
    Application::GlobalPar globalPar; 
    MIO::SaveIldgPar       ildgPar;

    globalPar.runId = "Test_ildg_io";
    globalPar.trajCounter.start = 1;
    globalPar.trajCounter.end   = 2;
    globalPar.trajCounter.step  = 1;

    application.setPar(globalPar);
    application.createModule<MGauge::Unit>("lattice");

    ildgPar.gauge         = "lattice";          // name of gauge field
    ildgPar.ensembleLabel = "su" + std::to_string(Nc) + "gauge"; // add suffix gauge_fixed_su3
    ildgPar.ensembleId    = "telos";       // collaboration label
  
    ildgPar.gaugeGroup    = "su";

    ildgPar.fileStem      = "ildg_full_double";     // stem of filename
    ildgPar.precision     = "double";
    ildgPar.reducedFormat = false;
    application.createModule<MIO::SaveIldg>("save-lat-full-double", ildgPar);

    ildgPar.fileStem      = "ildg_full_single";     // stem of filename
    ildgPar.precision     = "single";
    ildgPar.reducedFormat = false;
    application.createModule<MIO::SaveIldg>("save-lat-full-single", ildgPar);

    ildgPar.fileStem      = "ildg_red_double";     // stem of filename
    ildgPar.precision     = "double";
    ildgPar.reducedFormat = true;
    application.createModule<MIO::SaveIldg>("save-lat-reduced-double", ildgPar);

    ildgPar.fileStem      = "ildg_red_single";     // stem of filename
    ildgPar.precision     = "single";
    ildgPar.reducedFormat = true;
    application.createModule<MIO::SaveIldg>("save-lat-reduced-single", ildgPar);

    application.run();

    Grid_finalize();
    
    return EXIT_SUCCESS;
}
