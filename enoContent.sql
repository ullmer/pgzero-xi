-- Enodia content resolver tables      --
-- By Brygg Ullmer, Clemson University --
-- Begun 2023-04-06                    --

create table enoContentEntry(
;

create table enoContentAbbrev(
  id     integer unique primary key,
  abbrev text,
  count  integer
);

--- end ---
