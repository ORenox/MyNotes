



```
industrial-monitoring/
│
├── config/
│   ├── settings/
│   │   ├── base.py
│   │   ├── development.py
│   │   └── production.py
│   │
│   ├── urls.py
│   └── wsgi.py
│
├── apps/
│   │
│   ├── machines/
│   │   ├── models.py
│   │   ├── serializers.py
│   │   ├── views.py
│   │   ├── urls.py
│   │   └── tests/
│   │
│   ├── sensors/
│   │   ├── models.py
│   │   ├── serializers.py
│   │   ├── views.py
│   │   └── tests/
│   │
│   ├── maintenance/
│   │   ├── models.py
│   │   ├── serializers.py
│   │   ├── views.py
│   │   └── tests/
│   │
│   └── alerts/
│       ├── models.py
│       ├── serializers.py
│       ├── views.py
│       └── tests/
│
├── requirements.txt
├── Dockerfile
├── docker-compose.yml
├── pytest.ini
└── .github/
    └── workflows/
        └── ci.yml
```
