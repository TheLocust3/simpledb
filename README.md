# simple-db

A dead simple database, built for learning purposes. Algorithms and inspiration from
[Database Internals](https://www.oreilly.com/library/view/database-internals/9781492040330/).

## todo

- Fix deletion bugs (there seem to be a lot)
- Free pages from memory so only root stays in memory inbetween btree traversals
- Better page manager
  - Currently I'm just reading/writing to a file and letting Linux cache everything
- Lock Manager
- Some sort of query frontend
