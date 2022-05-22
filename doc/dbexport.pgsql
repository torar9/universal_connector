--
-- PostgreSQL database dump
--

-- Dumped from database version 14.2 (Ubuntu 14.2-1ubuntu1)
-- Dumped by pg_dump version 14.2 (Ubuntu 14.2-1ubuntu1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: insys; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA insys;


ALTER SCHEMA insys OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: device; Type: TABLE; Schema: insys; Owner: postgres
--

CREATE TABLE insys.device (
    device_id character varying(64) NOT NULL,
    create_timestamp timestamp with time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE insys.device OWNER TO postgres;

--
-- Name: measurement; Type: TABLE; Schema: insys; Owner: postgres
--

CREATE TABLE insys.measurement (
    measurement_id bigint NOT NULL,
    create_timestamp timestamp with time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    device_id character varying(64) NOT NULL,
    data json[] NOT NULL
);


ALTER TABLE insys.measurement OWNER TO postgres;

--
-- Name: measurement_measurement_id_seq; Type: SEQUENCE; Schema: insys; Owner: postgres
--

ALTER TABLE insys.measurement ALTER COLUMN measurement_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME insys.measurement_measurement_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Data for Name: device; Type: TABLE DATA; Schema: insys; Owner: postgres
--

COPY insys.device (device_id, create_timestamp) FROM stdin;
test2	2022-05-18 22:26:41.810604+02
esp32	2022-05-18 22:29:42.912153+02
\.


--
-- Data for Name: measurement; Type: TABLE DATA; Schema: insys; Owner: postgres
--

COPY insys.measurement (measurement_id, create_timestamp, device_id, data) FROM stdin;
1	2022-05-18 23:32:57.259241+02	esp32	{"{\\"sensor_name\\":\\"HTU21D\\",\\"temperature\\":23.48519135,\\"humidity\\":29.05706787}","{\\"sensor_name\\":\\"PT1000\\",\\"temperature\\":22.54103088}"}
\.


--
-- Name: measurement_measurement_id_seq; Type: SEQUENCE SET; Schema: insys; Owner: postgres
--

SELECT pg_catalog.setval('insys.measurement_measurement_id_seq', 1, true);


--
-- Name: device device_pkey; Type: CONSTRAINT; Schema: insys; Owner: postgres
--

ALTER TABLE ONLY insys.device
    ADD CONSTRAINT device_pkey PRIMARY KEY (device_id);


--
-- Name: measurement measurement_pkey; Type: CONSTRAINT; Schema: insys; Owner: postgres
--

ALTER TABLE ONLY insys.measurement
    ADD CONSTRAINT measurement_pkey PRIMARY KEY (measurement_id);


--
-- PostgreSQL database dump complete
--

