# DetectSubqueries
Sometimes, in an embedded query is better to have a go on running a sub-query alone. When your database system accept embedded queries. Note that MySQL doesn't accept them. This program is a go on isolating all the "SELECT" sub-queries in a query, by returning a list of all queries and sub-queries with no theoretical deep limit.
