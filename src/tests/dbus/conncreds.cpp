//  OpenVPN 3 Linux client -- Next generation OpenVPN client
//
//  Copyright (C) 2017      OpenVPN Inc. <sales@openvpn.net>
//  Copyright (C) 2017      David Sommerseth <davids@openvpn.net>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, version 3 of the License
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/**
 * @file   conncreds.cpp
 *
 * @brief  Simple test program reporting back the credentials of
 *         a running D-Bus service.  Input is the D-Bus bus name,
 *         either the well known bus name (like net.openvpn.v3.sessions)
 *         or the unique bus name (:1.39).  The output is PID and the users
 *         UID providing this service.
 */

#include <iostream>
#include "dbus/core.hpp"
#include "dbus/connection-creds.hpp"

using namespace openvpn;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <D-Bus bus name>" << std::endl;
        return 2;
    }

    std::string busname(argv[1]);
    DBus conn(G_BUS_TYPE_SYSTEM);
    conn.Connect();
    DBusConnectionCreds creds(conn);

    uid_t uid = creds.GetUID(busname);
    pid_t pid = creds.GetPID(busname);

    std::cout << "Querying credential information for bus name '"
              << busname << "' ... " << std::endl
              << "      User ID: " << std::to_string(uid)
              << std::endl
              << "   Process ID: " << std::to_string(pid)
              << std::endl;
    return 0;
}