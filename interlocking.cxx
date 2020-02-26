#include "interlocking.hxx"

EWRB::InterLocking::InterLocking(EWRB::LeverFrame* lever_frame)
{
    _lever_frame = lever_frame;


    // Qt is not happy without having at least one template entry

    _signal_lever_connections = {{1,{new FrameLever, {new Signal, EWRB::SignalState::Off}}}};
    _point_lever_connections = {{13, {new FrameLever, new Points}}};

    _setup_block_sections();
    _add_points();
    _add_signals();
    _connect_levers();
    _create_logic_table();

}

void EWRB::InterLocking::_create_logic_table()
{
    _logic[1] = {};                            // Lever 1 requires no conditions

    _logic[2] = {{EWRB::LeverState::On,
                    {{13, EWRB::LeverState::On},
                     {3, EWRB::LeverState::Off}}}, // Lever 2 released only if points 13 set to reverse, 3 Lever off
                 {EWRB::LeverState::Off, {}}       // No condition to return lever to OFF
                };

    _logic[3] = {{EWRB::LeverState::On,
                    {{13, EWRB::LeverState::Off},
                     {15, EWRB::LeverState::Off},
                     {28, EWRB::LeverState::Off},  // Lever 3 released only if points 13 & 15 set to normal,
                     {2, EWRB::LeverState::Off}}}, // SIG. 28 set to ON, 2 Lever Off
                 {EWRB::LeverState::Off, {}}       // No condition to return lever to OFF
                };

    _logic[4] = {};                                // Lever 4 requires no conditions

    _logic[5] = {{EWRB::LeverState::On,
                  {{21, EWRB::LeverState::On},
                  {22, EWRB::LeverState::Off},
                  {6, EWRB::LeverState::Off},
                  {10, EWRB::LeverState::Off},
                  {7, EWRB::LeverState::Off},      // Lever 5 released only if points 21 set to reverse, 22 set to normal,
                  {32, EWRB::LeverState::Off}}},   // SIG. 32 SIG. 7, SIG. 10 & SIG. 6 set to ON
                 {EWRB::LeverState::Off, {}}       // No condition to return lever to OFF
                };


    _logic[6] = {{EWRB::LeverState::On,
                  {{20, EWRB::LeverState::Off},
                     {21, EWRB::LeverState::Off},
                     {22, EWRB::LeverState::Off},  // Lever 6 released only if points 20, 21 & 22 set to normal,
                     {5, EWRB::LeverState::Off},   // SIG. 32 SIG. 7, SIG. 10 & SIG. 5 set to ON
                     {7, EWRB::LeverState::Off},
                     {10, EWRB::LeverState::Off},
                     {32, EWRB::LeverState::Off}}},
                 {EWRB::LeverState::Off, {}}
                };

    _logic[7] = {{EWRB::LeverState::On,
                  {{19, EWRB::LeverState::On},
                  {22, EWRB::LeverState::On},
                  {6, EWRB::LeverState::Off},
                  {10, EWRB::LeverState::Off},
                  {5, EWRB::LeverState::Off},      // Lever 7 released only if points 22 & 19 set to reverse
                  {32, EWRB::LeverState::Off}}},   // SIG. 32 SIG. 5, SIG. 10 & SIG. 6 set to ON
                 {EWRB::LeverState::Off, {}}       // No condition to return lever to OFF
                };

    _logic[8] = {};                                // Lever 8 requires no conditions as all point settings are valid routes

    _logic[9] = {};                                // Lever 9 is disused so has no conditions

    _logic[10] = {{EWRB::LeverState::On,
                   {{17, EWRB::LeverState::On},
                    {19, EWRB::LeverState::Off},
                    {22, EWRB::LeverState::On},
                    {5, EWRB::LeverState::Off},
                    {32, EWRB::LeverState::Off},
                   {7, EWRB::LeverState::Off},     // Lever 10 release only if points 17 & 22 set to reverse, points 19 set to normal
                   {6, EWRB::LeverState::Off}}},   // SIG. 6, SIG. 7, SIG. 5 & SIG. 32 set to ON
                  {EWRB::LeverState::Off, {}}      // No condition to return lever to OFF
                 };

    _logic[11] = {{EWRB::LeverState::On,
                   {{26, EWRB::LeverState::Off}}},  // Lever 11 release only if points 26 set to normal
                  {EWRB::LeverState::Off, {}}       // No condition to return lever to OFF
                 };

    _logic[12] = {{EWRB::LeverState::On,
                   {{26, EWRB::LeverState::On},
                    {38, EWRB::LeverState::Off}}},  // Lever 11 release only if points 26 set to normal, SIG. 38 set to ON
                  {EWRB::LeverState::Off, {}}       // No condition to return lever to OFF
                 };

    _logic[13] = {{EWRB::LeverState::On,            // Points 13 can only be changed when SIG. 2, SIG. 28 are ON
                   {{2, EWRB::LeverState::Off},
                    {3, EWRB::LeverState::Off},
                    {28, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                   {{2, EWRB::LeverState::Off},
                    {3, EWRB::LeverState::Off},
                    {28, EWRB::LeverState::Off}}}
                 };

    _logic[14] = {{EWRB::LeverState::On,            // Points 14 can only be changed when SIG. 8, SIG. 29 & SIG. 30 are ON
                   {{8, EWRB::LeverState::Off},
                   {29, EWRB::LeverState::Off},
                   {30, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                    {{8, EWRB::LeverState::Off},
                    {29, EWRB::LeverState::Off},
                    {30, EWRB::LeverState::Off}}}
                  };

    _logic[15] = {{EWRB::LeverState::On,            // Points 15 can only be changed when SIG. 28 & SIG. 29 are ON
                   {{28, EWRB::LeverState::Off},
                    {29, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::On,
                   {{28, EWRB::LeverState::Off},
                    {29, EWRB::LeverState::Off}}}
                 };

    _logic[16] = {};                                // Lever 16 is a spare

    _logic[17] = {{EWRB::LeverState::On,            // Points 17 can only be changed when SIG. 10 is ON
                   {{10, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                   {{10, EWRB::LeverState::Off}}}
                 };

    _logic[18] = {};                                // Lever 18 is a spare

    _logic[19] = {{EWRB::LeverState::On,            // Points 19 can only be changed when SIG. 7 & SIG. 10 are ON
                   {{7, EWRB::LeverState::Off},
                   {10, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                       {{7, EWRB::LeverState::Off},
                       {10, EWRB::LeverState::Off}}}
                   };

    _logic[20] = {{EWRB::LeverState::On,           // Points 20 can only be changed when SIG. 6, SIG. 5, SIG. 7 are ON
                   {{6, EWRB::LeverState::Off},    // and SIG. 33 is set to ON or left branch. Points 23 at Normal.
                    {5, EWRB::LeverState::Off},
                    {23, EWRB::LeverState::Off},
                    {7, EWRB::LeverState::Off},
                    {34, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off},
                    {32, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                   {{6, EWRB::LeverState::Off},
                   {5, EWRB::LeverState::Off},
                    {7, EWRB::LeverState::Off},
                    {23, EWRB::LeverState::Off},
                   {34, EWRB::LeverState::Off},
                   {35, EWRB::LeverState::Off},
                   {32, EWRB::LeverState::Off}}}
                 };

    _logic[21] = {{EWRB::LeverState::On,           // Points 21 can only be changed when SIG. 6, SIG. 5, SIG. 7 are ON
                   {{6, EWRB::LeverState::Off},    // and SIG. 33 is set to ON or left branch. Points 22 at Normal.
                    {5, EWRB::LeverState::Off},
                    {7, EWRB::LeverState::Off},
                    {34, EWRB::LeverState::Off},
                    {22, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off},
                    {32, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                   {{6, EWRB::LeverState::Off},
                   {5, EWRB::LeverState::Off},
                    {7, EWRB::LeverState::Off},
                    {22, EWRB::LeverState::Off},
                   {34, EWRB::LeverState::Off},
                   {35, EWRB::LeverState::Off},
                   {32, EWRB::LeverState::Off}}}
                 };

    _logic[22] = {{EWRB::LeverState::On,           // Points 22 can only be changed when SIG. 6, SIG. 5, SIG. 7 are ON
                   {{6, EWRB::LeverState::Off},
                    {5, EWRB::LeverState::Off},
                    {7, EWRB::LeverState::Off},
                    {32, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                   {{6, EWRB::LeverState::Off},
                   {5, EWRB::LeverState::Off},
                    {7, EWRB::LeverState::Off},
                   {32, EWRB::LeverState::Off}}}
                 };

    _logic[23] = {{EWRB::LeverState::On,           // Points 23 can only be changed when SIG. 6, SIG. 5, SIG. 33 are ON
                   {{6, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off},
                    {34, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off},
                    {32, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                   {{6, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off},
                   {34, EWRB::LeverState::Off},
                   {35, EWRB::LeverState::Off},
                   {32, EWRB::LeverState::Off}}}
                 };

    _logic[24] = {};                                //TODO EMERGENCY LEVER 1, LEVER 2
    _logic[25] = {};

    _logic[26] = {{EWRB::LeverState::On,            // Points 26 can only be changed when SIG. 11 and SIG. 38 are ON
                   {{11, EWRB::LeverState::Off},     // Points 26 reverse requires points 27 to be reverse
                    {12, EWRB::LeverState::Off},
                    {27, EWRB::LeverState::On},
                    {38, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                     {{11, EWRB::LeverState::Off},
                      {12, EWRB::LeverState::Off},
                      {38, EWRB::LeverState::Off}}}
                 };

    _logic[27] = {{EWRB::LeverState::On,            // Points 27 can only be changed when SIG. 37 and SIG. 38 are ON
                   {{37, EWRB::LeverState::Off},
                    {38, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off,
                     {{37, EWRB::LeverState::Off},
                      {26, EWRB::LeverState::Off},  // Points 27 normal requires Points 26 to be normal
                      {38, EWRB::LeverState::Off}}}
                 };

    _logic[28] = {{EWRB::LeverState::On,            // Lever 28 can only be changed if points 15 set to reverse and 14 to normal
                   {{15, EWRB::LeverState::On},
                    {8, EWRB::LeverState::Off},     // Shunt SIG. 8 to be ON
                    {14, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off, {}}
                 };

    _logic[29] = {{EWRB::LeverState::On,            // Lever 28 can only be changed if points 15 set to normal and 14 to normal
                   {{15, EWRB::LeverState::Off},    // Shunt SIG. 8 to be ON
                    {8, EWRB::LeverState::Off},
                    {14, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off, {}}
                 };

    _logic[30] = {{EWRB::LeverState::On,            // Lever 28 can only be changed if points 14 are set to reverse
                    {{8, EWRB::LeverState::Off},     // Shunt SIG. 8 to be ON
                    {14, EWRB::LeverState::On}}},
                  {EWRB::LeverState::Off, {}}
                 };

    _logic[31] = {};                                 // Lever 31 has no conditions

    _logic[32] = {{EWRB::LeverState::On,            // Lever 32 can only be changed if SIG. 10, SIG. 7, SIG. 6, SIG.5 are ON
                {{10, EWRB::LeverState::Off},       // and points 20 are set to normal
                 {20, EWRB::LeverState::Off},
                {7, EWRB::LeverState::Off},
                {6, EWRB::LeverState::Off},
                {5, EWRB::LeverState::Off}}}, {EWRB::LeverState::Off, {}}};

    _logic[33] = {{EWRB::LeverState::On,            // Lever 33 can only be changed if points 23 are reversed
                   {{23, EWRB::LeverState::On},     // and other aspect levers are off
                    {34, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off}}},
                    {EWRB::LeverState::Off, {}}
                 };

    _logic[34] = {{EWRB::LeverState::On,            // Lever 34 can only be changed if points 23, 20 are normal
                   {{23, EWRB::LeverState::Off},    // and other aspect levers are off
                    {20, EWRB::LeverState::Off},
                    {21, EWRB::LeverState::Off},
                    {33, EWRB::LeverState::Off},
                    {35, EWRB::LeverState::Off}}},
                    {EWRB::LeverState::Off, {}}
                 };

    _logic[35] = {{EWRB::LeverState::On,            // Lever 34 can only be changed if points 23 are normal, 20 are reversed
                   {{23, EWRB::LeverState::Off},    // and other aspect levers are off
                    {20, EWRB::LeverState::On},
                    {33, EWRB::LeverState::Off},
                    {34, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off, {}}
               };

    _logic[36] = {};                                // Lever 36 has no conditions

    _logic[37] = {{EWRB::LeverState::On,            // Lever 37 can only be changed if points 27 are reversed, SIG. 38 is ON
                   {{27, EWRB::LeverState::On},
                    {38, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off, {}}};

    _logic[38] = {{EWRB::LeverState::On,            // Lever 37 can only be changed if points 26, 27 are normal, SIG. 37 is ON
                   {{27, EWRB::LeverState::Off},
                    {26, EWRB::LeverState::Off},
                    {37, EWRB::LeverState::Off}}},
                  {EWRB::LeverState::Off, {}}};

}

void EWRB::InterLocking::update(const int& i)
{
    if(!_logic.keys().contains(i)) return;    // Safety for dev purposes in case all levers not set up yet

    lever_logic _temp = _logic[i];

    interlock_coordinate _coords = _temp[reverse(_lever_frame->operator[](i)->getState())];

    for(auto lever : _coords.keys())
    {
        bool toLock = _lever_frame->operator[](lever)->getState() != _coords[lever] && _lever_frame->operator[](lever)->getState() != EWRB::LeverState::Mid;

        if(toLock) qDebug() << "Lever "<< i << " Locked by Lever " << lever << " !";
        _lever_frame->operator[](i)->Lock(toLock);
        if(toLock) return;
    }

    qDebug() << "Moving Lever " << i;

    // As lever move successful, lock all levers which have this lever as a requirement and the state is not met

    for(auto lever : _coords.keys())
    {
        lever_logic _lever_log = _logic[lever];
        if(_lever_log[reverse(_lever_frame->operator[](lever)->getState())].contains(i))
        {
            // Checks that not only the lever is present in other lever lock definition, but attempted move is not a valid
            if(_lever_log[reverse(_lever_frame->operator[](lever)->getState())][i] != reverse(_lever_frame->operator[](i)->getState()))
            {
                qDebug() << "Locking Lever " << lever;
                _lever_frame->operator[](lever)->Lock(true);
            }
            else
            {
                qDebug() << "Releasing Lever " << lever;
                _lever_frame->operator[](lever)->Lock(false);
            }
        }
    }



}

void EWRB::InterLocking::_perform_action(const int& i)
{
    if(_signal_lever_connections.contains(i))
    {
        lever_active_signal_state state = _signal_lever_connections[i].second;

        // If attempting lever on and the block is occupied then do not release signal
        if(reverse(_lever_frame->operator[](i)->getState()) != EWRB::LeverState::Off && state.first->protectedBlockOccupied())
        {
            qDebug() << "Could not release signal " << state.first->id() << ", Block Occupied";
            return;
        }
        else if(reverse(_lever_frame->operator[](i)->getState()) == EWRB::LeverState::On)
        {
            qDebug() << "Setting Signal " << state.first->id() << " to On";
            state.first->setOn(true);
        }
        else
        {
            qDebug() << "Clearing Signal " << state.first->id() << " to Off: Aspect " << int(state.first->getState());
            state.first->tryClear(state.second);
        }
    }
}

bool EWRB::InterLocking::Query(const int& id)
{
    update(id);

    if(_lever_frame->operator[](id)->isLocked())
    {
        _lever_frame->operator[](id)->moveLever(EWRB::LeverState::Mid);
        return false;
    }
    else
    {
        _lever_frame->operator[](id)->moveLever();
    }

    _perform_action(id);

    return true;
}

void EWRB::InterLocking::_connect(const int& id, EWRB::HomeLever* lever, EWRB::Signal* signal, EWRB::SignalState aspect)
{
    _signal_lever_connections[id] = {};
    _signal_lever_connections[id] = {lever, {signal, aspect}};
}

void EWRB::InterLocking::_connect(const int& id, EWRB::PointsLever* lever, EWRB::Points* points)
{
    _point_lever_connections[id] = {lever, points};
}

void EWRB::InterLocking::_setup_block_sections()
{
    _block_sections[1] = new EWRB::BlockSection(1, "EDGWARE ROAD EAST SIG. 1 SIG. 2");
    _block_sections[2] = new EWRB::BlockSection(2, "SIG 2. TO EAST PLAT 4 APPROACH");
    _block_sections[3] = new EWRB::BlockSection(3, "SIG 2. TO EDGWARE ROAD PLATFORM 3");
    _block_sections[4] = new EWRB::BlockSection(4, "EDGWARE ROAD PLATFORM 4");
    _block_sections[5] = new EWRB::BlockSection(5, "EDGWARE ROAD PLATFORM 2 WESTBOUND DEPART");
    _block_sections[6] = new EWRB::BlockSection(6, "EDGWARE ROAD PLATFORM 3 WESTBOUND DEPART");
    _block_sections[7] = new EWRB::BlockSection(7, "EDGWARE ROAD PLATFORM 4 WESTBOUND DEPART");
    _block_sections[8] = new EWRB::BlockSection(8, "EDGWARE ROAD SHUNT EAST APPROACH");
    _block_sections[9] = new EWRB::BlockSection(); // DISUSED BLOCK/SIGNAL
    _block_sections[10] = new EWRB::BlockSection(10, "EDGWARE ROAD SIDING SHUNT");
    _block_sections[11] = new EWRB::BlockSection(11, "PREAD ST JCT TO PADDINGTON (HCL)");
    _block_sections[12] = new EWRB::BlockSection(12, "PREAD ST JCT TO PADDINGTON (DL)");
    _block_sections[28] = new EWRB::BlockSection(28, "EDGWARE ROAD PLATFORM 3 EASTBOUND DEPART");
    _block_sections[29] = new EWRB::BlockSection(29, "EDGWARE ROAD PLATFORM 2 EASTBOUND DEPART");
    _block_sections[30] = new EWRB::BlockSection(30, "EDGWARE ROAD PLATFORM 1 EASTBOUND DEPART");
    _block_sections[31] = new EWRB::BlockSection(31, "EDGWARE ROAD PLATFORM 1");
    _block_sections[32] = new EWRB::BlockSection(32, "EDGWARE ROAD SHUNT WEST APPROACH");
    _block_sections[34] = new EWRB::BlockSection(34, "SIG. 33 TO EDGWARE ROAD PLATFORM 2");
    _block_sections[33] = new EWRB::BlockSection(33, "SIG. 33 TO EDGWARE ROAD PLATFORM 1");
    _block_sections[35] = new EWRB::BlockSection(35, "SIG. 33 TO EDGWARE ROAD PLATFORM 3");
    _block_sections[36] = new EWRB::BlockSection(36, "EDGWARE ROAD WEST SIG. 36 SIG. 33");
    _block_sections[37] = new EWRB::BlockSection(37, "PRAED ST JCN APPROACH FROM PADDINGTON (HCL)");
    _block_sections[38] = new EWRB::BlockSection(38, "PRAED ST JCN APPROACH FROM PADDINGTON (DL)");
    _block_sections[39] = new EWRB::BlockSection(39, "PADDINGTON HCL DEPART (OPX)");
    _block_sections[40] = new EWRB::BlockSection(40, "PADDINGTON DL DEPART (OPX)");
}

void EWRB::InterLocking::_add_points()
{
    _points[13] = new EWRB::Points(13);                                         // Platform 3/4 East Approach
    _points[15] = new EWRB::Points(15);                                         // East Crossover
    _points[17] = new EWRB::Points(17);                                         // Trap Points
    _points[15] = new EWRB::Points(19);                                         // Siding Access
    _points[20] = new EWRB::Points(20);                                         // West Crossover 1
    _points[21] = new EWRB::Points(21);                                         // West Crossover 2
    _points[22] = new EWRB::Points(22);                                         // Platform 4 spur
    _points[23] = new EWRB::Points(23);                                         // Platform 1 West Approach
    _points[26] = new EWRB::Points(26);                                         // Westbound Praed St Jct
    _points[27] = new EWRB::Points(27);                                         // Eastbound Praed St Jct

    _block_sections[2]->setBlockPoints(_points[13]);                            // require points to be set to reverse
    _block_sections[2]->setRequiredPointsState(EWRB::PointsState::Reverse);

    _block_sections[3]->setBlockPoints({_points[13], _points[15]});             // For Platform 3 Eastbound Arrival
    _block_sections[3]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Normal});


    _block_sections[5]->setBlockPoints({_points[21], _points[22]});             // Platform 2 Westbound Departure
    _block_sections[5]->setRequiredPointsState({EWRB::PointsState::Reverse, EWRB::PointsState::Normal});

    _block_sections[6]->setBlockPoints({_points[20], _points[22]});             // Platform 3 Westbound Departure
    _block_sections[6]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Normal});

    _block_sections[7]->setBlockPoints({_points[19], _points[22]});             // Platform 4 Westbound Departure
    _block_sections[7]->setRequiredPointsState({EWRB::PointsState::Reverse, EWRB::PointsState::Reverse});

    // More than one possible route: Format is for at least one route to be valid then test the particular case
    // for this case both options are valid for points 15
    _block_sections[8]->setBlockPoints({_points[14], _points[15], _points[15]});
    _block_sections[8]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Normal, EWRB::PointsState::Reverse});

    _block_sections[10]->setBlockPoints({_points[17], _points[19], _points[22]});       // Siding Departure
    _block_sections[10]->setRequiredPointsState({EWRB::PointsState::Reverse, EWRB::PointsState::Normal, EWRB::PointsState::Reverse});

    _block_sections[11]->setBlockPoints(_points[26]);                           // DL Paddington Praed St
    _block_sections[11]->setRequiredPointsState(EWRB::PointsState::Normal);

    _block_sections[12]->setBlockPoints(_points[26]);                           // HCL Paddington Praed St
    _block_sections[12]->setRequiredPointsState(EWRB::PointsState::Reverse);

    _block_sections[28]->setBlockPoints({_points[15], _points[14]});                           // For Platform 3 Eastbound Depart
    _block_sections[28]->setRequiredPointsState({EWRB::PointsState::Reverse, EWRB::PointsState::Normal});

    _block_sections[29]->setBlockPoints({_points[15], _points[14]});                           // For Platform 2 Eastbound Depart
    _block_sections[29]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Normal});

    _block_sections[30]->setBlockPoints(_points[14]);                           // For Platform 2 Eastbound Depart
    _block_sections[30]->setRequiredPointsState(EWRB::PointsState::Reverse);

    // More than one possible route: Format is for at least one route to be valid then test the particular case
    // for this case both options are valid for points 21
    _block_sections[32]->setBlockPoints({_points[22], _points[21], _points[21]});
    _block_sections[32]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Normal, EWRB::PointsState::Reverse});

    _block_sections[33]->setBlockPoints(_points[23]);                           // Platform 1 Approach
    _block_sections[33]->setRequiredPointsState(EWRB::PointsState::Reverse);

    _block_sections[34]->setBlockPoints({_points[23], _points[20]});            // Platform 2 West Approach
    _block_sections[34]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Normal});

    _block_sections[35]->setBlockPoints({_points[23], _points[20]});            // Platform 2 West Approach
    _block_sections[35]->setRequiredPointsState({EWRB::PointsState::Normal, EWRB::PointsState::Reverse});

    _block_sections[37]->setBlockPoints(_points[27]);                           // HCL Paddington to Praed St Jct
    _block_sections[37]->setRequiredPointsState(EWRB::PointsState::Reverse);

    _block_sections[38]->setBlockPoints(_points[27]);                           // DL Paddington to Praed St Jct
    _block_sections[38]->setRequiredPointsState(EWRB::PointsState::Normal);
}

void EWRB::InterLocking::_add_signals()
{
    _signals[1] = new EWRB::Signal(1);                                      // Edgware Road East SIG. 1
    _block_sections[1]->setBlockSignal(_signals[1]);
    _block_sections[1]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[2] = new EWRB::Signal(2);                                      // Edgware Road East Jct Feather Pos 1 SIG. 2, 3
    _block_sections[2]->setBlockSignal(_signals[2]);                        // Edgware Road East Jct
    _block_sections[2]->setRequiredState(EWRB::SignalState::OffJctLeft);    // Diverge Left
    _block_sections[3]->setBlockSignal(_signals[2]);
    _block_sections[3]->setRequiredState(EWRB::SignalState::Off);           // Straight ahead

    _signals[4] = new EWRB::Signal(4);                                      // Platform 4 Approach SIG. 4
    _block_sections[4]->setBlockSignal(_signals[4]);
    _block_sections[4]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[5] = new EWRB::Signal(5);
    _block_sections[5]->setBlockSignal(_signals[5]);                        // Westbound Starter Platform 2 SIG. 5
    _block_sections[5]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[6] = new EWRB::Signal(6);
    _block_sections[6]->setBlockSignal(_signals[6]);                        // Westbound Starter Platform 3 SIG. 6
    _block_sections[6]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[7] = new EWRB::Signal(7);
    _block_sections[7]->setBlockSignal(_signals[7]);                        // Westbound Starter Platform 4 SIG. 7
    _block_sections[7]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[8] = new EWRB::ShuntSignal(8);
    _block_sections[8]->setBlockSignal(_signals[8]);                        // Edgware Road Eastbound Wrong Dir. SIG. 8
    _block_sections[8]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal

    // Signal 9 absent

    _signals[10] = new EWRB::ShuntSignal(10);
    _block_sections[10]->setBlockSignal(_signals[10]);                      // Edgware Road Siding SIG. 10
    _block_sections[10]->setRequiredState(EWRB::SignalState::Off);          // Disc 2AT Signal

    _signals[11] = new EWRB::Signal(11);
    _block_sections[11]->setBlockSignal(_signals[11]);                       // Praed St Junction Feather Pos 2
    _block_sections[11]->setRequiredState(EWRB::SignalState::Off);           // Towards Paddington DL
    _block_sections[12]->setBlockSignal(_signals[11]);
    _block_sections[12]->setRequiredState(EWRB::SignalState::OffJctRight);   // Towards Paddington HCL

    _signals[28] = new EWRB::Signal(28);
    _block_sections[28]->setBlockSignal(_signals[28]);                       // Eastbound Starter Platform 3 SIG. 28
    _block_sections[28]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[29] = new EWRB::Signal(29);
    _block_sections[29]->setBlockSignal(_signals[29]);                       // Eastbound Starter Platform 2 SIG. 29
    _block_sections[29]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[30] = new EWRB::Signal(30);
    _block_sections[30]->setBlockSignal(_signals[30]);                       // Eastbound Starter Platform 1 SIG. 30
    _block_sections[30]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[31] = new EWRB::Signal(31);
    _block_sections[31]->setBlockSignal(_signals[31]);                       // Platform 1 Approach SIG. 31
    _block_sections[31]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[32] = new EWRB::ShuntSignal(32);
    _block_sections[32]->setBlockSignal(_signals[32]);                       // Edgware Road Westbound Wrong Dir. SIG. 32
    _block_sections[32]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal

    _signals[33] = new EWRB::Signal(33);
    _block_sections[33]->setBlockSignal(_signals[33]);                       // Edgware Road East Jct Feather Pos 1, 2 SIG. 33, 34, 35
    _block_sections[33]->setRequiredState(EWRB::SignalState::OffJctRight);   // Routed to Platform 3
    _block_sections[34]->setBlockSignal(_signals[33]);
    _block_sections[34]->setRequiredState(EWRB::SignalState::Off);           // Routed to Platform 2
    _block_sections[35]->setBlockSignal(_signals[33]);
    _block_sections[35]->setRequiredState(EWRB::SignalState::OffJctLeft);    // Routed to Platform 1

    _signals[36] = new EWRB::Signal(36);
    _block_sections[36]->setBlockSignal(_signals[36]);                       // Edgware Road Westbound Approach
    _block_sections[36]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[37] = new EWRB::Signal(37);
    _block_sections[37]->setBlockSignal(_signals[37]);                       // Praed St Jct Approach from HCL Paddington
    _block_sections[37]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    _signals[38] = new EWRB::Signal(38);
    _block_sections[38]->setBlockSignal(_signals[38]);                       // Praed St Jct Approach from HCL Paddington
    _block_sections[38]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal

    // OPX Controlled Signals

    _signals[39] = new EWRB::Signal(39);
    _block_sections[39]->setBlockSignal(_signals[39]);                       // Paddington HCL Depart
    _block_sections[39]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal

    _signals[40] = new EWRB::Signal(40);
    _block_sections[40]->setBlockSignal(_signals[40]);                       // Paddington DL Depart
    _block_sections[40]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal

}

void EWRB::InterLocking::_connect_levers()
{
    for(int i{1}; i < 13; ++i)
    {
        if(i == 2) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[2], EWRB::SignalState::OffJctLeft);
        else if(i == 3) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[2], EWRB::SignalState::Off);
        else if(i == 9) continue;
        else if(i == 11) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[11], EWRB::SignalState::Off);
        else if(i == 12) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[11], EWRB::SignalState::OffJctRight);
        else _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[i]);
    }

    for(int i{13}; i < 28; ++i)
    {
        if(i == 24 || i == 25) continue;
        else _connect(i, (PointsLever*)_lever_frame->operator[](i), _points[i]);
    }

    for(int i{28}; i < 39; ++i)
    {
        if(i == 33) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[33], EWRB::SignalState::OffJctLeft);
        else if(i == 34) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[33], EWRB::SignalState::Off);
        else if(i == 35) _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[33], EWRB::SignalState::OffJctRight);
        else _connect(i, (HomeLever*)_lever_frame->operator[](i), _signals[i]);
    }

}

