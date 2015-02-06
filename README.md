# RBL-tools
*Library and toolset for checking realtime blackhole lists*

------

## ckRBL

With ckrbl you can check any IP on the terminal via
```
ckrbl [options] IP
```

ckRBL is shipped with a default set of realtime blacklists and all can be checked with only one command. *Please note, that for many blacklists you'll need an enterprise license for commercial use. All listed blacklists are free for private use. Contact the blacklist provider for more information!*

You are able to integrate ckrbl in your applications, due ckrbl sets an exit-status of zero if the IP was not blacklisted on any blacklist or 255, if it was blacklisted on one ore more blacklists. So you are able to check your servers IP with e.g. nagios regular.

Avivable options:

| short option | meaning |
| ------------ | ------- |
| -b           | Blacklist domains to be checked. Multiple domains should be separated by spaces, comma or semicolon. |
| -B           | Blacklist file containing blacklist domains to be checked. Should contain one domain per line. |
| -h           | Print help |
| -l           | Print only blacklists, where IP was listed. |
| -q           | Print nothing |

Exit-codes:

| exit-code | meaning |
| --------- | ------- |
| 0         | IP was not listed on any blacklist |
| 255       | IP was listed on one or more blacklists |
| 1         | An error occured |


## libRBL

If you want to integrate realtime blacklists checks into your application, you don't need to call ckrbl, but you could use the librbl API.

It is a very simple API, due it has only to do DNS lookups. Transform your IP (v4 / v6) with rbl_atoip() to an reverse noted IP (if you didn't already) and afterwards you can check your IP with rbl_lookup().

*In the moment librbl is not able to return the TXT record, but this will be integrated soon.*


## Contribute

If you want to contribute to this project, fork this git, do whatever you want and make a pull-request.

If you want to add more blacklists, feel free to do so, but follow these conventions:

- Block providers together and seperate providers by 2 blank lines, e.g.
```
# some provider
a.someprover.com


# another provider
a.nother.provider.com
```

- blacklist entrys inside a provider block are separated by a single blank line
- add a small description in front of each blacklist entry
- there must not be more than 80 characters per line
- add only blacklists, that don't need a license for private / small usage


## License

rbl-tools is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but **without any warranty**; without even the implied warranty of **merchantability** or **fitness for a particular purpose**. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License and GNU Lesser General Public License along with this program. If not, see http://www.gnu.org/licenses/.

Copyright (C) 2015 Alexander Haase <alexander.haase@rwth-aachen.de>
