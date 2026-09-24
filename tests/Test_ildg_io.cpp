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

    Application appSaveConfigs, appLoadConfigs;

    Application::GlobalPar globalPar; 
    MIO::SaveIldgPar       saveIldgPar;
    MIO::LoadIldgPar       loadIldgPar;

    globalPar.runId = "saveIldg";
    globalPar.trajCounter.start = 1;
    globalPar.trajCounter.end   = 2;
    globalPar.trajCounter.step  = 1;

    appSaveConfigs.setPar(globalPar);

    // generate random SU(Nc) cfgs
    appSaveConfigs.createModule<MGauge::Random>("lattice");

    // save cfgs in different formats
    saveIldgPar.gauge         = "lattice";          // name of gauge field
    saveIldgPar.ensembleId    = "telos";            // collaboration label
    saveIldgPar.ensembleLabel = "su" + std::to_string(Nc) + "unit_gauge";
    saveIldgPar.gaugeGroup    = "su";

    saveIldgPar.fileStem      = "ildg_full_double";     // stem of filename
    saveIldgPar.precision     = "double";
    saveIldgPar.reducedFormat = false;
    appSaveConfigs.createModule<MIO::SaveIldg>("save-lat-full-double", saveIldgPar);

    saveIldgPar.fileStem      = "ildg_full_single";     // stem of filename
    saveIldgPar.precision     = "single";
    saveIldgPar.reducedFormat = false;
    appSaveConfigs.createModule<MIO::SaveIldg>("save-lat-full-single", saveIldgPar);

    saveIldgPar.fileStem      = "ildg_red_double";     // stem of filename
    saveIldgPar.precision     = "double";
    saveIldgPar.reducedFormat = true;
    appSaveConfigs.createModule<MIO::SaveIldg>("save-lat-reduced-double", saveIldgPar);

    saveIldgPar.fileStem      = "ildg_red_single";     // stem of filename
    saveIldgPar.precision     = "single";
    saveIldgPar.reducedFormat = true;
    appSaveConfigs.createModule<MIO::SaveIldg>("save-lat-reduced-single", saveIldgPar);
    
    appSaveConfigs.run();

    // read the cfgs back
    globalPar.runId = "loadIldg";
    appLoadConfigs.setPar(globalPar);
  
    loadIldgPar.fileStem = "ildg_full_double";
    appLoadConfigs.createModule<MIO::LoadIldg>("load-lat-full-double", loadIldgPar);

    loadIldgPar.fileStem = "ildg_full_single";
    appLoadConfigs.createModule<MIO::LoadIldg>("load-lat-full-single", loadIldgPar);

    loadIldgPar.fileStem = "ildg_red_double";
    appLoadConfigs.createModule<MIO::LoadIldg>("load-lat-reduced-double", loadIldgPar);

    loadIldgPar.fileStem = "ildg_red_single";
    appLoadConfigs.createModule<MIO::LoadIldg>("load-lat-reduced-single", loadIldgPar);

    appLoadConfigs.run();

    Grid_finalize();
    
    return EXIT_SUCCESS;
}
