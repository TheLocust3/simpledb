# simple-db

A dead simple database, built for learning purposes. Algorithms and inspiration from
[Database Internals](https://www.oreilly.com/library/view/database-internals/9781492040330/).

## todo

- Fix concurrency bugs
- Better lock manager
  - Separate read and write locks (2 phase locking)
- Better page manager
  - Currently I'm just reading/writing to a file and letting Linux cache everything
  - Utilize `mmap` and turn off system level caches
- More complete query functionality
  - Currently there's a very basic query langauge that can't really be use for much but testing
- Collect database metrics over time
