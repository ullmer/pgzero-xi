-- Enodia content resolver tables      --
-- By Brygg Ullmer, Clemson University --
-- Begun 2023-04-06                    --

create table contentServerEntry(
  id          integer unique primary key,
  fullAddress text,   -- e.g., 'https://enodia.computing.clemson.edu/'
  abbrev      text,   -- e.g., 'ecce'
  abbrevCount integer -- e.g., 1
;

create table contentServerAbbrev(
  id     integer unique primary key,
  abbrev text,
  count  integer
);

create table spreadDetails(
  id integer unique primary key,
  serverId  integer, -- contentServerEntry.id
);

--- end ---
